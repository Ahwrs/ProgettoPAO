#include "SubTaskEntry.h"
#include <QBoxLayout>

////////////////
// Costruttore
////////////////

SubTaskEntry::SubTaskEntry(Activity* act, QWidget* parent) : QWidget(parent), editable(act){

    QVBoxLayout* layout = new QVBoxLayout(this);

    TitleField = new QLineEdit();
    DescField = new QTextEdit();
    DescField->setMaximumHeight(80);

    if (!act) {

        id = QUuid();
        TitleField->setPlaceholderText("Titolo della Sotto-Attività");
        DescField->setPlaceholderText("Descrizione della Sotto-Attività");

    } else {

        id = act->getID();
        TitleField->setText(act->getTitle());
        DescField->setText(act->getDescription());
    }

    layout->addWidget(TitleField);
    layout->addWidget(DescField);
}

////////////////
// Raccoglitore dati
////////////////

SubTaskData SubTaskEntry::collectData() const {
    
    SubTaskData data;
    data.id = id;
    data.title = TitleField->text();
    data.description = DescField->toPlainText();
    return data;
}