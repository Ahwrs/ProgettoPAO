#include "SubTaskEntry.h"
#include <QBoxLayout>

SubTaskEntry::SubTaskEntry(Activity* act, QWidget* p) : QWidget(p){

    editable = act;

    QVBoxLayout* box = new QVBoxLayout(this);
    TitleField = new QLineEdit();
    DescField = new QTextEdit();

    if(!act){

        id = QUuid();
        TitleField->setPlaceholderText("Titolo della Sotto-Attività");
        DescField->setPlaceholderText("Descrizione della Sotto-Attività");
    }
    else{

        id = act->getID();
        TitleField->setText(act->getTitle());
        DescField->setText(act->getDescription());
    }

    box->addWidget(TitleField);
    box->addWidget(DescField);
}

SubTaskData SubTaskEntry::collectData() const{

    SubTaskData data;
    data.id = id;
    data.title = TitleField->text();
    data.description = DescField->toPlainText();   

    return data;
}