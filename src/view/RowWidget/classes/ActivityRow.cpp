#include "ActivityRow.h"


ActivityRow::ActivityRow(Activity* a, QWidget* p): QWidget(p), act(a){

    box = new QVBoxLayout(this);

    header = new QLabel();
    content = nullptr;
    expand = new QPushButton();
    
    del = new QPushButton("Elimina");
    del->setIcon(QApplication::style()->standardIcon(QStyle::SP_TrashIcon));

    del->setStyleSheet(
        "QPushButton {"
        "   border: 2px solid #D32F2F;"  
        "   border-radius: 6px;"      
        "   padding: 5px 10px;"          
        "   color: #D32F2F;"             
        "   background-color: transparent;"
        "}"
        "QPushButton:hover {"
        "   background-color: #FFEBEE;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #FFCDD2;"
        "}"
    );

    connect(del, &QPushButton::clicked, this, [this]{

        QString msg = "Procedendo si eliminera' l'attivita' definitivamente. Continuare?";
        if(QMessageBox::question(this, "Attenzione", msg) == QMessageBox::Yes) emit remove(act->getID());

    });

    QWidget* HBox = new QWidget();
    QHBoxLayout* HLayout = new QHBoxLayout(HBox);

    header->setText(a->getTitle());
    HLayout->addWidget(header);

    expand->setText(">");
    connect(expand, &QPushButton::clicked, this, [this]{

        if(!content) return;
        bool isV = content->isVisible();
        content->setVisible(!isV);
        expand->setText(isV ? ">":"∧");
    });

    HLayout->addStretch();
    HLayout->addWidget(expand);
    box->addWidget(HBox);
}   

void ActivityRow::addContent(QWidget* c) {

    content = c;
    content->hide();
    box->addWidget(content);
}

void ActivityRow::closeContent() {
    if (content) {
        content->hide();
        expand->setText(">"); 
    }
}