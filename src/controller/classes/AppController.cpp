#include "AppController.h"
#include "Filters.h"
#include "RowFactory.h"
#include "ActivityForm.h"
#include "DetailViewFactory.h"
#include "ConfirmPopup.h"
#include "SavePopup.h"
#include "ErrorPopup.h"

#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QTimer>

////////////////
// Costruttore
////////////////
AppController::AppController(ActivityManager* m, MainWindow* w, QObject* parent) : QObject(parent), manager(m), window(w){
    
    curDay = window->getDayView()->currentDate();

    // Segnali dalla vista giornaliera
    connect(window->getDayView(), &DayViewWidget::dayChanged, this, [this](QDate newDate) {
        
        curDay = newDate;
        refreshList();
    });
    connect(window->getDayView(), &DayViewWidget::searchCriteriaChanged, this, &AppController::onSearchChanged);
    connect(window->getDayView(), &DayViewWidget::newActivityRequested, this, &AppController::newActivity);

    // Segnali dal manager
    connect(manager, &ActivityManager::activitiesChanged, this, [this] {
        refreshList();
        if (searchActive) onSearchChanged(lastSearch);
    });
    connect(manager, &ActivityManager::IOError, this, [this](const QString& msg) {
        ErrorPopup* popup = new ErrorPopup("Errore di caricamento:\n" + msg);
        popup->showCenteredTop(window);
    });

    // Segnali dalla finestra principale
    connect(window, &MainWindow::openWorkingFileRequested, this, &AppController::openFile);
    connect(window, &MainWindow::saveRequested, this, &AppController::saveRequested);
    connect(window, &MainWindow::closing, this, [this] {
        if (!workFile.isEmpty()) manager->save(workFile);
    });
    connect(window, &MainWindow::newActivityShortcut, this, &AppController::newActivity);
    connect(window, &MainWindow::saveShortcut, this, &AppController::saveShortcut);
    connect(window, &MainWindow::saveAsShortcut, this, &AppController::saveAsShortcut);

    // Caricamento automatico all'avvio (posticipato)
    QTimer::singleShot(0, this, [this] {
        QSettings settings("ProgettoPAO", "Calendar");
        QString last = settings.value("lastWorkingFile", "").toString();

        if (!last.isEmpty() && QFile::exists(last)) {
            QFileInfo info(last);
            ConfirmPopup* popup = new ConfirmPopup(
                QString("Riprendere il lavoro su '%1'?").arg(info.fileName()));

            connect(popup, &ConfirmPopup::confirmed, this, [this, last, info] {
                workFile = last;
                window->setCurrentFile(info.fileName());
                manager->load(last);
            });
            popup->showCenteredTop(window);
        }
    });

    refreshList();
}

////////////////
// refreshList – Ricarica la vista giornaliera
////////////////
void AppController::refreshList()
{
    auto taskBranch = std::make_unique<CompositeFilter>(CompositeFilter::LogicMode::Or);
    taskBranch->addFilter(std::make_unique<CategoryFilter>(Activity::ActivityCategory::SimpleTask));
    taskBranch->addFilter(std::make_unique<CategoryFilter>(Activity::ActivityCategory::CompositeTask));

    auto dateRange = std::make_unique<DateRangeFilter>(curDay, curDay);

    CompositeFilter dayFilter(CompositeFilter::LogicMode::Or);
    dayFilter.addFilter(std::move(taskBranch));
    dayFilter.addFilter(std::move(dateRange));

    std::vector<Activity*> results = manager->search(dayFilter);

    std::vector<ActivityRow*> taskRows;
    std::vector<ActivityRow*> eventRows;

    for (Activity* act : results) {
        ActivityRow* row = buildRow(act);

        if (TaskRow* taskRow = dynamic_cast<TaskRow*>(row)) {
            connect(taskRow, &TaskRow::completeReq, this, [this](const QUuid& id) {
                manager->completeTask(id);
            });
            taskRows.push_back(row);
        } else if (auto* eventRow = dynamic_cast<EventRow*>(row)) {
            connect(eventRow, &EventRow::viewDetailsRequested, this, &AppController::viewDetails);
            eventRows.push_back(row);
        }
    }

    window->getDayView()->setTaskRows(taskRows);
    window->getDayView()->setEventRows(eventRows);
}

////////////////
// openForm – Mostra il form per creare/modificare
////////////////
void AppController::openForm(Activity* toEdit)
{
    ActivityForm* form = new ActivityForm(toEdit);

    connect(form, &ActivityForm::submitCreate, this, [this](const ActivityData& data) {
        manager->create(data);
        window->showDayView();
    });
    connect(form, &ActivityForm::submitEdit, this, [this](const QUuid& id, const ActivityData& data) {
        manager->edit(id, data);
        window->showDayView();
    });
    connect(form, &ActivityForm::cancelled, this, [this] {
        window->showDayView();
    });

    window->showForm(form);
}

////////////////
// buildRow – Crea una riga e collega i segnali base
////////////////
ActivityRow* AppController::buildRow(Activity* act)
{
    ActivityRow* row = createRow(act);

    connect(row, &ActivityRow::edit, this, &AppController::editActivity);
    connect(row, &ActivityRow::remove, this, [this](const QUuid& id) {
        manager->del(id);
    });

    if (auto* taskRow = dynamic_cast<TaskRow*>(row)) {
        connect(taskRow, &TaskRow::completeReq, this, [this](const QUuid& id) {
            manager->completeTask(id);
        });
    } else if (auto* eventRow = dynamic_cast<EventRow*>(row)) {
        connect(eventRow, &EventRow::viewDetailsRequested, this, &AppController::viewDetails);
    }

    return row;
}

////////////////
// saveFile – Salva sul file corrente
////////////////
void AppController::saveFile()
{
    if (!workFile.isEmpty()) manager->save(workFile);
}

////////////////
// saveAsFile – Salva con nuovo nome
////////////////
void AppController::saveAsFile()
{
    QString path = QFileDialog::getSaveFileName(window, "Salva con nome", QString(), "File Calendario (*.json)");
    if (path.isEmpty()) return;

    workFile = path;
    window->setCurrentFile(QFileInfo(path).fileName());
    manager->save(path);

    QSettings settings("ProgettoPAO", "Calendar");
    settings.setValue("lastWorkingFile", path);
}

////////////////
// Slot: newActivity
////////////////
void AppController::newActivity()
{
    openForm(nullptr);
}

////////////////
// Slot: editActivity
////////////////
void AppController::editActivity(const QUuid& id)
{
    if (Activity* act = manager->findByID(id)) openForm(act);
}

////////////////
// Slot: viewDetails
////////////////
void AppController::viewDetails(const QUuid& id)
{
    Activity* act = manager->findByID(id);
    if (!act) return;

    EventDetailView* view = createDetailView(act);
    if (!view) return;

    connect(view, &EventDetailView::editRequested, this, [this](const QUuid& editId) {
        if (Activity* toEdit = manager->findByID(editId)) openForm(toEdit);
    });
    connect(view, &EventDetailView::deleteRequested, this, [this](const QUuid& delId) {
        manager->del(delId);
        window->showDayView();
    });
    connect(view, &EventDetailView::backRequested, this, [this] {
        window->showDayView();
    });

    window->showForm(view);
}

////////////////
// Slot: onSearchChanged
////////////////
void AppController::onSearchChanged(const SearchCriteria& c)
{
    bool active = !c.title.isEmpty() || c.hasCategory || c.hasStartDate || c.hasEndDate;
    lastSearch = c;
    searchActive = active;

    if (!active) {
        window->getDayView()->clearSearch();
        return;
    }

    CompositeFilter filter(CompositeFilter::LogicMode::And);
    if (!c.title.isEmpty())
        filter.addFilter(std::make_unique<TitleFilter>(c.title));
    if (c.hasCategory)
        filter.addFilter(std::make_unique<CategoryFilter>(c.category));
    if (c.hasStartDate)
        filter.addFilter(std::make_unique<DateRangeFilter>(c.startDate, c.hasEndDate ? c.endDate : c.startDate));

    std::vector<Activity*> results = manager->search(filter);
    std::vector<ActivityRow*> rows;
    for (Activity* act : results) rows.push_back(buildRow(act));

    window->getDayView()->setSearchResults(rows);
}

////////////////
// Slot: openFile
////////////////
void AppController::openFile()
{
    QString path = QFileDialog::getOpenFileName(window, "Apri file di lavoro", QString(), "File Calendario (*.json)");
    if (path.isEmpty()) return;

    if (manager->load(path)) {
        workFile = path;
        window->setCurrentFile(QFileInfo(path).fileName());
        QSettings settings("ProgettoPAO", "Calendar");
        settings.setValue("lastWorkingFile", path);
    }
}

////////////////
// Slot: saveRequested
////////////////
void AppController::saveRequested()
{
    SavePopup* popup = new SavePopup(!workFile.isEmpty(), window);
    connect(popup, &SavePopup::saveRequested, this, [this] { saveFile(); });
    connect(popup, &SavePopup::saveAsRequested, this, [this] { saveAsFile(); });
    popup->showCenteredTop(window);
}

////////////////
// Slot: saveShortcut
////////////////
void AppController::saveShortcut()
{
    if (workFile.isEmpty()) saveAsFile();
    else saveFile();
}

////////////////
// Slot: saveAsShortcut
////////////////
void AppController::saveAsShortcut()
{
    saveAsFile();
}