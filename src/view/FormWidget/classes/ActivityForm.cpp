#include "ActivityForm.h"
#include "SubTaskEntry.h"
#include "Appointment.h"
#include "SimpleTask.h"
#include "CompositeTask.h"
#include "ErrorPopup.h"

#include <QPushButton>

////////////////
// Costruttore
////////////////

ActivityForm::ActivityForm(Activity* toEdit, QWidget* parent) : QWidget(parent), editable(toEdit) {
    
    setAttribute(Qt::WA_StyledBackground, true);
    setupUI();
    setupConnections();
    loadExistingData();
    setStyleSheet(styleSheetString());
}

////////////////
// Setup dell'interfaccia
////////////////

void ActivityForm::setupUI(){

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(24, 20, 24, 20);
    mainLayout->setSpacing(12);

    QWidget* container = new QWidget();
    container->setLayout(mainLayout);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(container);

    QVBoxLayout* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->addWidget(scrollArea);

    // Intestazione
    QLabel* headerLabel = new QLabel("Nuova Attività");
    headerLabel->setFixedHeight(40);
    headerLabel->setObjectName("mainLabel");
    mainLayout->addWidget(headerLabel, Qt::AlignHCenter);

    // Titolo
    TitleField = new QLineEdit();
    TitleLabel = new QLabel("Titolo");
    TitleLabel->setFixedHeight(30);
    TitleField->setPlaceholderText("Titolo attività...");
    TitleField->setContextMenuPolicy(Qt::NoContextMenu);
    mainLayout->addWidget(TitleLabel);
    mainLayout->addWidget(TitleField);

    // Descrizione
    DescField = new QTextEdit();
    DescLabel = new QLabel("Descrizione");
    DescLabel->setFixedHeight(30);
    DescField->setPlaceholderText("Descrizione attività...");
    DescField->setContextMenuPolicy(Qt::NoContextMenu);
    DescField->setFixedHeight(60);
    DescField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->addWidget(DescLabel);
    mainLayout->addWidget(DescField);

    // Modalità (Event / Task)
    TaskMode = new QCheckBox("Event / Task");
    mainLayout->addWidget(TaskMode);

    ////////////////////////////////
    // Pannello Event (visibile in modalità Event)
    ////////////////////////////////
    
    EventPanel = new QWidget();
    QVBoxLayout* eventLayout = new QVBoxLayout(EventPanel);

    // Data
    QHBoxLayout* dateRow = new QHBoxLayout();
    QLabel* dateIcon = new QLabel();
    dateIcon->setPixmap(QIcon(":/Date.svg").pixmap(16, 16));
    dateRow->addWidget(dateIcon);
    dateRow->addWidget(new QLabel("Data"));
    dateRow->addStretch();
    DateField = new QDateEdit();
    DateField->setDisplayFormat("dd/MM/yyyy");
    DateField->setDate(QDate::currentDate());
    dateRow->addWidget(DateField);
    eventLayout->addLayout(dateRow);

    // Ora inizio / fine
    QHBoxLayout* timeRow = new QHBoxLayout();
    QLabel* timeIcon = new QLabel();
    timeIcon->setPixmap(QIcon(":/Time.svg").pixmap(16, 16));
    timeRow->addWidget(timeIcon);
    timeRow->addWidget(new QLabel("Inizio - Fine"));
    timeRow->addStretch();
    StartField = new QTimeEdit();
    StartField->setDisplayFormat("HH:mm");
    StartField->setTime(QTime::currentTime());
    timeRow->addWidget(StartField);
    timeRow->addSpacing(10);
    EndField = new QTimeEdit();
    EndField->setDisplayFormat("HH:mm");
    EndField->setTime(QTime::currentTime().addSecs(3600));
    timeRow->addWidget(EndField);
    eventLayout->addLayout(timeRow);

    // Link (per Appointment)
    QHBoxLayout* linkRow = new QHBoxLayout();
    QLabel* linkIcon = new QLabel();
    linkIcon->setPixmap(QIcon(":/Link.svg").pixmap(16, 16));

    QWidget* linkContainer = new QWidget();
    linkContainer->setObjectName("linkWidget");
    QHBoxLayout* linkInnerLayout = new QHBoxLayout(linkContainer);
    linkInnerLayout->setContentsMargins(0, 0, 0, 0);
    linkInnerLayout->setSpacing(0);

    QLabel* linkPrefix = new QLabel("https://");
    linkPrefix->setObjectName("linkLabel");

    LinkField = new QLineEdit();
    LinkField->setPlaceholderText("esempio.com");
    LinkField->setFrame(false);
    LinkField->setContextMenuPolicy(Qt::NoContextMenu);

    linkInnerLayout->addWidget(linkPrefix);
    linkInnerLayout->addWidget(LinkField);

    OnlineCheck = new QCheckBox("Evento online");

    linkRow->addWidget(linkIcon);
    linkRow->addWidget(linkContainer, 1);
    linkRow->addSpacing(10);
    linkRow->addWidget(OnlineCheck);

    eventLayout->addLayout(linkRow);
    mainLayout->addWidget(EventPanel);

    //////////////////////////////////
    // Pannello Task (visibile in modalità Task)
    //////////////////////////////////
    TaskPanel = new QWidget();
    TaskPanel->setObjectName("TaskWidget");

    QVBoxLayout* taskLayout = new QVBoxLayout(TaskPanel);
    taskLayout->setContentsMargins(10, 10, 10, 15);
    taskLayout->setSpacing(10);

    QLabel* subTaskLabel = new QLabel("Sub Tasks");
    subTaskLabel->setFixedHeight(20);
    taskLayout->addWidget(subTaskLabel, 0, Qt::AlignHCenter | Qt::AlignTop);

    SubTaskLayout = new QVBoxLayout();
    SubTaskLayout->setContentsMargins(0, 0, 0, 0);
    SubTaskLayout->setSpacing(8);
    SubTaskLayout->setAlignment(Qt::AlignTop);
    taskLayout->addLayout(SubTaskLayout);

    addSubBtn = new QPushButton("Aggiungi sottotask");
    addSubBtn->setObjectName("Add");
    removeSubBtn = new QPushButton("Rimuovi sottotask");
    removeSubBtn->setObjectName("Remove");

    QHBoxLayout* subBtnLayout = new QHBoxLayout();
    subBtnLayout->addWidget(addSubBtn);
    subBtnLayout->addWidget(removeSubBtn);
    taskLayout->addLayout(subBtnLayout);

    TaskPanel->hide();
    mainLayout->addWidget(TaskPanel);

    //////////////////////////////////
    // Pulsanti
    //////////////////////////////////
    saveBtn = new QPushButton("Salva");
    saveBtn->setObjectName("SButton");
    cancelBtn = new QPushButton("Annulla");
    cancelBtn->setObjectName("CButton");

    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(cancelBtn);
}

////////////////
// Connessioni segnali/slot
////////////////

void ActivityForm::setupConnections(){

    // Commutazione tra modalità Event e Task
    connect(TaskMode, &QCheckBox::toggled, this, [this](bool isTask) {

        EventPanel->setVisible(!isTask);
        TaskPanel->setVisible(isTask);

        bool showDesc = !(isTask && SubTaskLayout->count() > 0);
        DescField->setVisible(showDesc);
        if (!DescField->isVisible()) {
            DescField->setText("");
        }
        DescLabel->setVisible(showDesc);
    });

    // Aggiungi sottotask
    connect(addSubBtn, &QPushButton::clicked, this, [this]() {

        SubTaskEntry* entry = new SubTaskEntry();
        SubTaskLayout->addWidget(entry);

        bool showDesc = (SubTaskLayout->count() == 0);
        DescField->setVisible(showDesc);
        if (!DescField->isVisible()) {
            DescField->setText("");
        }
        DescLabel->setVisible(showDesc);
    });

    // Rimuovi sottotask (ultimo)
    connect(removeSubBtn, &QPushButton::clicked, this, [this]() {

        QLayoutItem* item = SubTaskLayout->takeAt(SubTaskLayout->count() - 1);
        if (item && item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;

        bool showDesc = (SubTaskLayout->count() == 0);
        DescField->setVisible(showDesc);
        DescLabel->setVisible(showDesc);
    });

    // Salva
    connect(saveBtn, &QPushButton::clicked, this, [this]() {

        ActivityData data = collectData();

        // Validazione: titolo obbligatorio
        if (data.title.trimmed().isEmpty()) {

            ErrorPopup* error = new ErrorPopup("Errore. \nTitolo obbligatorio per l'inserimento.");
            error->showCenteredTop(TitleField, 30);
            return;
        }

        // Validazione SubTask: se ha descrizione deve avere titolo
        if (TaskMode->isChecked()) {

            for (int i = 0; i < SubTaskLayout->count(); ++i) {

                auto* entry = qobject_cast<SubTaskEntry*>(SubTaskLayout->itemAt(i)->widget());
                if (!entry) continue;

                SubTaskData sd = entry->collectData();
                if (sd.title.trimmed().isEmpty() && !sd.description.trimmed().isEmpty()) {

                    ErrorPopup* error = new ErrorPopup("Errore. \nOgni sotto-attività con una descrizione deve avere anche un titolo.");
                    error->showCenteredTop(TitleField, 30);
                    return;
                }
            }
        }

        // Validazione Event/Appointment
        if (data.type == Activity::ActivityCategory::Event ||
            data.type == Activity::ActivityCategory::Appointment) {

            if (data.start >= data.end) {

                ErrorPopup* error = new ErrorPopup("Errore. \nL'orario di inizio deve precedere l'orario di fine.");
                error->showCenteredTop(TitleField, 30);
                return;
            }
            if (data.isOnline && data.link.isEmpty()) {

                ErrorPopup* error = new ErrorPopup("Errore. \nLink necessario.");
                error->showCenteredTop(TitleField, 30);
                return;
            }
        }

        // Emissione segnale
        if (editable) {

            emit submitEdit(editable->getID(), data);

        } else {

            emit submitCreate(data);
        }
    });

    // Annulla
    connect(cancelBtn, &QPushButton::clicked, this, [this]() {

        emit cancelled();
    });
}

////////////////
// Caricamento dati in modifica
////////////////

void ActivityForm::loadExistingData()
{
    if (!editable) return;

    TitleField->setText(editable->getTitle());

    bool isTask = (dynamic_cast<Task*>(editable) != nullptr);
    TaskMode->setChecked(isTask);
    TaskMode->setEnabled(false);

    if (Event* ev = dynamic_cast<Event*>(editable)) {

        DescField->setText(ev->getDescription());
        DateField->setDate(ev->getDate());
        StartField->setTime(ev->getStartTime());
        EndField->setTime(ev->getEndTime());

        if (Appointment* ap = dynamic_cast<Appointment*>(ev)) {

            LinkField->setText(ap->getLink());
            OnlineCheck->setChecked(ap->getIsOnline());
        } else {

            LinkField->setReadOnly(true);
            OnlineCheck->setEnabled(false);
        }
    } else if (SimpleTask* st = dynamic_cast<SimpleTask*>(editable)) {

        DescField->setText(st->getDescription());
        addSubBtn->setVisible(false);
        removeSubBtn->setVisible(false);

        QVBoxLayout* taskLayout = qobject_cast<QVBoxLayout*>(TaskPanel->layout());

        if (taskLayout) {

            QLabel* infoLabel = new QLabel("Impossibile aggiungere Sub-Tasks");
            infoLabel->setAlignment(Qt::AlignHCenter);
            taskLayout->addWidget(infoLabel, 0, Qt::AlignHCenter);
        }
    } else if (CompositeTask* ct = dynamic_cast<CompositeTask*>(editable)) {

        DescField->hide();

        for (const auto& sub : ct->getSubTasks()) {

            SubTaskEntry* entry = new SubTaskEntry(sub.get());
            SubTaskLayout->addWidget(entry);
        }
    }
}

////////////////
// Raccolta dati dal form
////////////////

ActivityData ActivityForm::collectData() const
{
    ActivityData data;

    data.title = TitleField->text().trimmed();
    data.description = DescField->toPlainText();

    if (TaskMode->isChecked()) {

        // Modalità Task
        for (int i = 0; i < SubTaskLayout->count(); ++i) {

            QWidget* w = SubTaskLayout->itemAt(i)->widget();
            auto* entry = qobject_cast<SubTaskEntry*>(w);
            if (!entry) continue;

            SubTaskData sd = entry->collectData();
            if (!sd.title.trimmed().isEmpty()) {

                data.subTasks.push_back(sd);
            }
        }

        data.type = data.subTasks.empty()
                    ? Activity::ActivityCategory::SimpleTask
                    : Activity::ActivityCategory::CompositeTask;
    } else {

        // Modalità Event
        data.date = DateField->date();
        data.start = StartField->time();
        data.end = EndField->time();
        data.link = LinkField->text();
        data.isOnline = OnlineCheck->isChecked();

        data.type = data.link.isEmpty()
                    ? Activity::ActivityCategory::Event
                    : Activity::ActivityCategory::Appointment;
    }

    return data;
}

////////////////
// QSS
////////////////

QString ActivityForm::styleSheetString() const
{
    return
        "QWidget {"
        "   background-color: transparent;"
        "   color: #E8E8E8;"
        "   font-family: Segoe UI;"
        "   font-size: 10pt;"
        "}"
        "#mainLabel {"
        "   border-bottom: 1px solid gray;"
        "   padding-bottom: 5px;"
        "   color: white;"
        "   font-size: 20pt;"
        "   font-weight: 700;"
        "}"
        "#linkWidget {"
        "    background: #3A3F4B;"
        "    border: 1px solid #3A3F4B;"
        "    border-radius: 8px;"
        "    padding: 8px 0px;"
        "}"
        "#linkLabel {"
        "    background: transparent;"
        "    color: #BDBDBD;"
        "    margin-right: 5px;"
        "    margin-left: 10px;"
        "}"
        "QLabel {"
        "   color: #E5E5E5;"
        "   font-weight: 600;"
        "}"
        "QLineEdit, QTextEdit {"
        "   background-color: #171A21;"
        "   color: white;"
        "   border: 1px solid #3A3F4B;"
        "   border-radius: 8px;"
        "   padding: 8px 12px;"
        "}"
        "QLineEdit:focus, QTextEdit:focus {"
        "   border: 1px solid #8B5CF6;"
        "}"
        "QLineEdit:read-only {"
        "    color: #555B6852;"
        "    background-color: #171A21;"
        "}"
        "QDateEdit, QTimeEdit {"
        "    background-color: #171A21;"
        "    color: #F2F2F2;"
        "    border: 1px solid #3A3F4B;"
        "    border-radius: 8px;"
        "    padding-left: 12px;"
        "    padding-right: 0px;"
        "    min-height: 32px;"
        "}"
        "QDateEdit:hover, QTimeEdit:hover {"
        "    border-color: #6B7280;"
        "}"
        "QDateEdit:focus, QTimeEdit:focus {"
        "    border: 1px solid #8B5CF6;"
        "}"
        "QDateEdit::up-button, QTimeEdit::up-button {"
        "    subcontrol-position: top right;"
        "    width: 20px;"
        "    height: 20px;"
        "    margin: 0px 10px -10px 0px;"
        "    background: transparent;"
        "}"
        "QDateEdit::down-button, QTimeEdit::down-button {"
        "    subcontrol-position: bottom right;"
        "    width: 20px;"
        "    height: 20px;"
        "    margin: -10px 10px 0px 0px;"
        "    background: transparent;"
        "}"
        "QDateEdit::up-arrow, QTimeEdit::up-arrow {"
        "    image: url(:/Up.svg);"
        "    width:15px;"
        "    height:15px;"
        "}"
        "QDateEdit::down-arrow, QTimeEdit::down-arrow {"
        "    image: url(:/Down.svg);"
        "    width:15px;"
        "    height:15px;"
        "}"
        "QCheckBox {"
        "   spacing:8px;"
        "   color:#E5E5E5;"
        "}"
        "QCheckBox::indicator {"
        "   width:17px;"
        "   height:17px;"
        "   border-radius:5px;"
        "   border:1px solid #555B68;"
        "   background-color: #171A21;"
        "}"
        "QCheckBox::indicator:hover {"
        "   border-color:#8B5CF6;"
        "}"
        "QCheckBox::indicator:checked {"
        "   background:#8B5CF6;"
        "   border-color:#8B5CF6;"
        "}"
        "QCheckBox:disabled {"
        "   color: #555B6852;"
        "}"
        "QCheckBox::indicator:disabled {"
        "   border-color: #555B6852;"
        "   background-color: #171A2152;"
        "}"
        "#TaskWidget {"
        "   border: 1px solid #3A3F4B;"
        "   border-radius: 6px;"
        "}"
        "#SButton, #Add {"
        "   border: 2px solid #2563EB;"
        "   border-radius: 6px;"
        "   padding: 5px 10px;"
        "   color: #2563EB;"
        "   background-color: transparent;"
        "   margin-top: 10%;"
        "   font-weight: 700;"
        "}"
        "#Add { margin-top: 0px; }"
        "#SButton:pressed, #SButton:hover,"
        "#Add:pressed, #Add:hover {"
        "   border: 2px solid #1D4ED8;"
        "   background-color: rgba(255, 255, 255, 25);"
        "}"
        "#Remove, #CButton {"
        "   border: 2px solid #D32F2F;"
        "   border-radius: 6px;"
        "   padding: 5px 10px;"
        "   color: #D32F2F;"
        "   background-color: transparent;"
        "   font-weight: 700;"
        "}"
        "#Remove:pressed, #Remove:hover,"
        "#CButton:pressed, #CButton:hover {"
        "   border: 2px solid red;"
        "   background-color: rgba(255, 255, 255, 25);"
        "}"
        "QScrollArea {"
        "   background: transparent;"
        "   border: none;"
        "}"
        "QScrollBar:vertical {"
        "   background: transparent;"
        "   width: 0px;"
        "}";
}