#include "ActivityForm.h"
#include "SubTaskEntry.h"
#include "Appointment.h"
#include "SimpleTask.h"
#include "CompositeTask.h"
#include <QPushButton>


ActivityForm::ActivityForm(Activity* toEdit, QWidget* parent) : QWidget(parent), editable(toEdit)
{

    setAttribute(Qt::WA_StyledBackground, true);

    QVBoxLayout* formLayout = new QVBoxLayout();
    formLayout->setContentsMargins(24,20,24,20);
    formLayout->setSpacing(12);

    QWidget* formContainer = new QWidget();
    formContainer->setLayout(formLayout);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(formContainer);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(scrollArea);

    QLabel* mainLabel = new QLabel("Nuova Attività");
    mainLabel->setFixedHeight(40);
    mainLabel->setObjectName("mainLabel");
    formLayout->addWidget(mainLabel, Qt::AlignHCenter);

    //----------------------------------
    // Titolo
    //----------------------------------

    TitleField = new QLineEdit();
    QLabel* titleLabel = new QLabel("Titolo");
    titleLabel->setFixedHeight(40);

    TitleField->setPlaceholderText("Titolo attività...");
    TitleField->setContextMenuPolicy(Qt::NoContextMenu);
    formLayout->addWidget(titleLabel);
    formLayout->addWidget(TitleField);

    //----------------------------------
    // Descrizione
    //----------------------------------
    DescField = new QTextEdit();
    QLabel* DescLabel = new QLabel("Descrizione");
    DescLabel->setFixedHeight(40);
    DescField->setPlaceholderText("Descrizione attività...");
    DescField->setContextMenuPolicy(Qt::NoContextMenu);
    DescField->setFixedHeight(50);
    DescField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    formLayout->addWidget(DescLabel);
    formLayout->addWidget(DescField);


    //----------------------------------
    // Tipo attività
    //----------------------------------

    isAllDay = new QCheckBox("Event / Task");
    formLayout->addWidget(isAllDay);

    //----------------------------------
    // EVENT WIDGET
    //----------------------------------

    EventWidget = new QWidget();

    QVBoxLayout* eventLayout = new QVBoxLayout(EventWidget);
    
    QHBoxLayout* dateLayout = new QHBoxLayout();
    DateField = new QDateEdit();
    QLabel* DIcon = new QLabel();
    DIcon->setPixmap(QIcon(":/Date.svg").pixmap(16,16));
    dateLayout->addWidget(DIcon);
    dateLayout->addWidget(new QLabel("Data"));
    dateLayout->addStretch();
    DateField->setDisplayFormat("dd/MM/yyyy");
    dateLayout->addWidget(DateField);
    
    QHBoxLayout* TimeLayout = new QHBoxLayout();
    StartField = new QTimeEdit();
    EndField = new QTimeEdit();
    StartField->setDisplayFormat("HH:mm");
    EndField->setDisplayFormat("HH:mm");
    
    QLabel* TIcon = new QLabel();
    TIcon->setPixmap(QIcon(":/Time.svg").pixmap(16,16));
    TimeLayout->addWidget(TIcon);
    TimeLayout->addWidget(new QLabel("Inizio - Fine"));
    TimeLayout->addStretch();
    TimeLayout->addWidget(StartField);
    TimeLayout->addSpacing(10);
    TimeLayout->addWidget(EndField);

    eventLayout->addLayout(dateLayout);
    eventLayout->addLayout(TimeLayout);

    //----------------------------------
    // EVENT WIDGET -- LINK
    //----------------------------------
    
    QHBoxLayout* row = new QHBoxLayout();

    QLabel* icon = new QLabel();
    icon->setPixmap(QIcon(":/Link.svg").pixmap(16,16));

    QWidget* linkWidget = new QWidget();
    linkWidget->setObjectName("linkWidget");

    QHBoxLayout* linkLayout = new QHBoxLayout(linkWidget);
    linkLayout->setContentsMargins(0,0,0,0);
    linkLayout->setSpacing(0);

    QLabel* prefix = new QLabel("https://");
    prefix->setObjectName("linkLabel");

    LinkField = new QLineEdit();
    LinkField->setPlaceholderText("esempio.com");
    LinkField->setFrame(false);
    LinkField->setContextMenuPolicy(Qt::NoContextMenu);

    linkLayout->addWidget(prefix);
    linkLayout->addWidget(LinkField);
    

    isOnlineField = new QCheckBox("Evento online");

    row->addWidget(icon);
    row->addWidget(linkWidget, 1);
    row->addSpacing(10);
    row->addWidget(isOnlineField);

    eventLayout->addLayout(row);
    formLayout->addWidget(EventWidget);



    //----------------------------------
    // TASK WIDGET
    //----------------------------------
    TaskWidget = new QWidget();

    QVBoxLayout* taskLayout = new QVBoxLayout(TaskWidget);
    taskLayout->setContentsMargins(0,0,0,0);
    taskLayout->setSpacing(10);

    taskLayout->addWidget(new QLabel("Sub Tasks"));

    SubTasks = new QVBoxLayout();
    SubTasks->setContentsMargins(0,0,0,0);
    SubTasks->setSpacing(8);
    SubTasks->setAlignment(Qt::AlignTop);

    taskLayout->addLayout(SubTasks);
    QPushButton* addTaskButton = new QPushButton("Aggiungi sottotask");
    QPushButton* removeTaskButton = new QPushButton("Rimuovi sottotask");    

    taskLayout->addWidget(addTaskButton);
    taskLayout->addWidget(removeTaskButton);
    TaskWidget->hide();
    formLayout->addWidget(TaskWidget);

    //----------------------------------
    // BOTTONI
    //----------------------------------

    QPushButton* saveButton = new QPushButton("Salva");
    QPushButton* cancelButton = new QPushButton("Annulla");
    formLayout->addWidget(saveButton);
    formLayout->addWidget(cancelButton);

    //----------------------------------
    // Connessioni
    //----------------------------------


    connect(isAllDay, &QCheckBox::toggled, this, [this](bool checked) {
        
        EventWidget->setVisible(!checked);
        TaskWidget->setVisible(checked);
        DescField->setVisible(!(checked && SubTasks->count() > 0));
    });

    connect(addTaskButton, &QPushButton::clicked, this, [this]() {

        SubTaskEntry* entry = new SubTaskEntry();
        SubTasks->addWidget(entry);
        DescField->setVisible(SubTasks->count() == 0);
    });
    connect(removeTaskButton, &QPushButton::clicked, this, [this]() {

        QLayoutItem* item = SubTasks->takeAt(SubTasks->count() - 1);
        if (item && item->widget()) item->widget()->deleteLater();
        delete item;
        if(SubTasks->count() == 0) DescField->setVisible(true);
    });

    connect(saveButton, &QPushButton::clicked, this, [this]() {

        ActivityData data = collectData();

        if(editable) emit submitEdit(editable->getID(), data);
        else emit submitCreate(data);

    });

    connect(cancelButton, &QPushButton::clicked, this, [this](){

        emit cancelled();
    });


    //----------------------------------
    // Caricamento dati
    //----------------------------------

    if(editable != nullptr)
    {

        TitleField->setText( editable->getTitle());

        bool task = dynamic_cast<Task*>(editable) != nullptr;
        isAllDay->setChecked(task);
        isAllDay->setEnabled(false);

        if(Event* e = dynamic_cast<Event*>(editable)) {

            DescField->setText(e->getDescription());
            DateField->setDate(e->getDate());

            StartField->setTime(e->getStartTime());
            EndField->setTime(e->getEndTime());

            if(Appointment* ap = dynamic_cast<Appointment*>(e)){
                
                LinkField->setText(ap->getLink());
                isOnlineField->setChecked(ap->getIsOnline());
            }
        }
        else if(SimpleTask* st = dynamic_cast<SimpleTask*>(editable)){

            DescField->setText(st->getDescription());
        }
        else if(CompositeTask* ct = dynamic_cast<CompositeTask*>(editable)){

            for(auto& sub : ct->getSubTasks()){
                
                DescField->hide();
                SubTaskEntry* entry = new SubTaskEntry(sub.get());
                SubTasks->addWidget(entry);
            }
        }

    }

    this->setStyleSheet(

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

        "QLineEdit,"
        "QTextEdit {"
        "   background-color: #171A21;"
        "   color: white;"
        "   border: 1px solid #3A3F4B;"
        "   border-radius: 8px;"
        "   padding: 8px 12px;"
        "}"

        "QLineEdit:focus,"
        "QTextEdit:focus {"
        "   border: 1px solid #8B5CF6;"
        "}"
        
        "QDateEdit,"
        "QTimeEdit"
        "{"
        "    background-color: #171A21;"
        "    color: #F2F2F2;"
        "    border: 1px solid #3A3F4B;"
        "    border-radius: 8px;"
        "    padding-left: 12px;"
        "    padding-right: 0px;"
        "    min-height: 32px;"
        "}"

        "QDateEdit:hover,"
        "QTimeEdit:hover"
        "{"
        "    border-color: #6B7280;"
        "}"

        "QDateEdit:focus,"
        "QTimeEdit:focus"
        "{"
        "    border: 1px solid #8B5CF6;"
        "}"

       "QDateEdit::up-button,"
        "QTimeEdit::up-button"
        "{"
        "    subcontrol-position: top right;"
        "    width: 20px;"
        "    height: 20px;"
        "    margin: 0px 10px -10px 0px;"
        "    background: transparent;"
        "}"

        "QDateEdit::down-button,"
        "QTimeEdit::down-button"
        "{"
        "    subcontrol-position: bottom right;"
        "    width: 20px;"
        "    height: 20px;"
        "    margin: -10px 10px 0px 0px;"
        "    background: transparent;"
        "}"

        "QDateEdit::up-arrow,"
        "QTimeEdit::up-arrow"
        "{"
        "    image: url(:/Up.svg);"

        "    width:15px;"
        "    height:15px;"
        "}"

        "QDateEdit::down-arrow,"
        "QTimeEdit::down-arrow {"

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
        "   background:#171A21;"
        "}"

        "QCheckBox::indicator:hover {"
        "   border-color:#8B5CF6;"
        "}"

        "QCheckBox::indicator:checked {"
        "   background:#8B5CF6;"
        "   border-color:#8B5CF6;"
        "}"

        "QPushButton {"
        "   background:#171A21;"
        "   color:white;"
        "   border-radius:8px;"
        "   border:1px solid #343946;"
        "   padding:10px;"
        "   font-weight:600;"
        "}"

        "QPushButton:hover {"
        "   background:#222631;"
        "   border-color:#8B5CF6;"
        "}"

        "QPushButton:pressed {"
        "   background:#111318;"
        "}"

        "QPushButton[text='Salva'] {"
        "   background:#7C3AED;"
        "   border:none;"
        "}"

        "QPushButton[text='Salva']:hover {"
        "   background:#8B5CF6;"
        "}"


        "QScrollArea {"
        "   background:transparent;"
        "   border:none;"
        "}"

        "QScrollBar:vertical {"
        "   background:transparent;"
        "   width:0px;"
        "}"

);

}

ActivityData ActivityForm::collectData() const{

    ActivityData data;

    
    data.description = DescField->toPlainText();
    data.title = TitleField->text().trimmed();
    if (data.title.isEmpty()) {
        // QMessageBox::warning(const_cast<ActivityForm*>(this), "Errore", "Il titolo è obbligatorio.");
    }
    if(isAllDay->isChecked()){

        for(int i=0; i<SubTasks->count(); ++i){

            QWidget* w = SubTasks->itemAt(i)->widget();
            auto* entry = qobject_cast<SubTaskEntry*>(w);

            if(!entry) continue;
            SubTaskData sd = entry->collectData();

            if(!sd.title.trimmed().isEmpty()) data.subTasks.push_back(sd);
        }

        data.type = data.subTasks.empty()
                    ? Activity::ActivityCategory::SimpleTask
                    : Activity::ActivityCategory::CompositeTask;

    }
    else
    {

        data.date = DateField->date();
        data.start = StartField->time();
        data.end = EndField->time();
        data.link = LinkField->text();
        data.isOnline = isOnlineField->isChecked();
        data.type = data.link.isEmpty()
                    ? Activity::ActivityCategory::Event
                    : Activity::ActivityCategory::Appointment;
    }

    return data;
}