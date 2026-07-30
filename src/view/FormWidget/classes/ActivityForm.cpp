#include "ActivityForm.h"
#include "SubTaskEntry.h"
#include "Appointment.h"
#include "SimpleTask.h"
#include "CompositeTask.h"

#include <QPushButton>

ActivityForm::ActivityForm(Activity* act, QWidget* p) : QWidget(p){

    editable = act;

    QVBoxLayout* box = new QVBoxLayout(this);
    TitleField = new QLineEdit();
    DescField = new QTextEdit();
    isAllDay = new QCheckBox("Tutto il giorno");

    box->addWidget(isAllDay);
    box->addWidget(TitleField);
    box->addWidget(DescField);

    QWidget* EventW = new QWidget();
    QVBoxLayout* EventBox = new QVBoxLayout(EventW);
    DateField = new QDateEdit();    EventBox->addWidget(DateField);
    StartField = new QTimeEdit();   EventBox->addWidget(StartField);
    EndField = new QTimeEdit();     EventBox->addWidget(EndField);  
    
    DateField->setDisplayFormat("dd/MM/yyyy");
    StartField->setDisplayFormat("HH:mm");
    EndField->setDisplayFormat("HH:mm");
    
    QHBoxLayout* linkBox = new QHBoxLayout();
    LinkField = new QLineEdit();                linkBox->addWidget(LinkField);
    isOnlineField = new QCheckBox("Online");    linkBox->addWidget(isOnlineField);

    EventBox->addLayout(linkBox);
    EventW->setVisible(true);
    box->addWidget(EventW);

    QWidget* TaskW = new QWidget();
    QPushButton* addTask = new QPushButton("Add");
    SubTasks = new QVBoxLayout(TaskW);
    SubTasks->addWidget(addTask);
    TaskW->setVisible(false);
    box->addWidget(TaskW);
    
    connect(isAllDay, &QCheckBox::toggled, this, [EventW, TaskW](bool checked) {

        EventW->setVisible(!checked);   
        TaskW->setVisible(checked); 
    });

    connect(addTask, &QPushButton::clicked, this, [this]{
        SubTaskEntry* se = new SubTaskEntry();
        SubTasks->addWidget(se);
    });

    if(!act){

        TitleField->setPlaceholderText("Titolo");
        DescField->setPlaceholderText("Descrizione");
        LinkField->setPlaceholderText("https://...");
       
    }
    else{

        TitleField->setText(act->getTitle());
        isAllDay->setChecked(dynamic_cast<Task*>(act) != nullptr);
        isAllDay->setEnabled(false);
        
        if(Event* e = dynamic_cast<Event*>(act)){

            DescField->setText(e->getDescription());
            DateField->setDate(e->getDate());
            StartField->setTime(e->getStartTime());
            EndField->setTime(e->getEndTime());
            
            if(Appointment* ap = dynamic_cast<Appointment*>(e)){

                LinkField->setText(ap->getLink());
                isOnlineField->setChecked(ap->getIsOnline());
            }
        }
        else if (SimpleTask* st = dynamic_cast<SimpleTask*>(act))
        {
            DescField->setText(st->getDescription());
        }
        else if (CompositeTask* ct = dynamic_cast<CompositeTask*>(act))
        {
            for(auto& st : ct->getSubTasks()){

                SubTaskEntry* ste = new SubTaskEntry(st.get());
                SubTasks->addWidget(ste);
            }
        }
        
        
    }

    QPushButton* saveBtn = new QPushButton("Salva");
    connect(saveBtn, &QPushButton::clicked, this, [this]{

        ActivityData data = collectData();

        if (editable) emit submitEdit(editable->getID(), data);
        else emit submitCreate(data);
    });
    QPushButton* cancelBtn = new QPushButton("Annulla");
    connect(cancelBtn, &QPushButton::clicked, this, [this]{ emit cancelled(); });

    box->addWidget(saveBtn);
    box->addWidget(cancelBtn);
}

ActivityData ActivityForm::collectData() const {

    ActivityData data;
    data.title = TitleField->text();
    data.description = DescField->toPlainText();   
    
    if (isAllDay->isChecked()) {
        
        for (int i = 0; i < SubTasks->count(); ++i) {

            auto* entry = qobject_cast<SubTaskEntry*>(SubTasks->itemAt(i)->widget());
            if (!entry) continue; 
            SubTaskData sd = entry->collectData();
            if (!sd.title.isEmpty()) data.subTasks.push_back(sd);
        }

        data.type = data.subTasks.empty()
        ? Activity::ActivityCategory::SimpleTask
        : Activity::ActivityCategory::CompositeTask;

    } else {

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