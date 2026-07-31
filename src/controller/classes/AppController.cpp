#include "AppController.h"
#include "Filters.h"
#include "RowFactory.h"
#include "ActivityForm.h"

AppController::AppController(ActivityManager* m, MainWindow* w, QObject* parent)
    : QObject(parent), manager(m), mainWindow(w)
{
    connect(mainWindow->getDayView(), &DayViewWidget::newActivityRequested, this, &AppController::onNewActivityRequested);
    connect(manager, &ActivityManager::activitiesChanged, this, &AppController::refreshActivityList);
    refreshActivityList();
}

void AppController::refreshActivityList() {

    CompositeFilter noFilter(CompositeFilter::LogicMode::And);
    std::vector<Activity*> results = manager->search(noFilter);

    std::vector<ActivityRow*> taskRows;
    std::vector<ActivityRow*> eventRows;

    for (Activity* act : results) {
        ActivityRow* row = createRow(act);
        connect(row, &ActivityRow::edit, this, &AppController::onEditRequested);
        connect(row, &ActivityRow::remove, this, [this](const QUuid& id){ manager->del(id); });

        if (TaskRow* taskRow = dynamic_cast<TaskRow*>(row)) {
            connect(taskRow, &TaskRow::completeReq, this, [this](const QUuid& id){ manager->completeTask(id); });
            taskRows.push_back(row);
        } else {
            eventRows.push_back(row);
        }
    }

    mainWindow->getDayView()->setTaskRows(taskRows);
    mainWindow->getDayView()->setEventRows(eventRows);
}


void AppController::openForm(Activity* toEdit) {

    ActivityForm* form = new ActivityForm(toEdit);

    connect(form, &ActivityForm::submitCreate, this, [this](const ActivityData& data){
        manager->create(data);
        mainWindow->showDayView();
    });
    connect(form, &ActivityForm::submitEdit, this, [this](const QUuid& id, const ActivityData& data){
        manager->edit(id, data);
        mainWindow->showDayView();
    });
    connect(form, &ActivityForm::cancelled, this, [this]{
        mainWindow->showDayView();
    });

    mainWindow->showForm(form);
}

void AppController::onNewActivityRequested() { openForm(nullptr); }
void AppController::onEditRequested(const QUuid& id) { 
    
    if (Activity* act = manager->findByID(id)) openForm(act);
}