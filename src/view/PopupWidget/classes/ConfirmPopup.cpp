#include "ConfirmPopup.h"
#include <QLabel>
#include <QPushButton>

////////////////
// Costruttore
////////////////

ConfirmPopup::ConfirmPopup(const QString& msg, QWidget* parent) : PopupWidget(parent){

    // Contenuto del popup    
    QWidget* content = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(content);

    // Messaggio
    QLabel* msgLabel = new QLabel(msg);
    layout->addWidget(msgLabel);

    // Pulsanti
    QHBoxLayout* btnLayout = new QHBoxLayout();

    QPushButton* confirmBtn = new QPushButton("Conferma");
    QPushButton* cancelBtn = new QPushButton("Annulla");
    confirmBtn->setObjectName("confirmBtn");
    cancelBtn->setObjectName("cancelBtn");

    connect(confirmBtn, &QPushButton::clicked, this, [this]() {

        emit confirmed();
        close();
    });

    connect(cancelBtn, &QPushButton::clicked, this, [this]() {

        emit cancelled();
        close();
    });

    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(confirmBtn);
    layout->addLayout(btnLayout);

    // Style
    setStyleSheet(
        "ConfirmPopup {"
        "   background-color: rgb(34, 30, 14);"
        "   border: 3px solid rgb(255, 215, 64);"
        "   border-radius: 6px;"
        "   padding: 5px 10px;"
        "}"
        "ConfirmPopup QLabel {"
        "   color: white;"
        "   font-size: 10pt;"
        "   margin-bottom: 30%;"
        "   font-weight: 600;"
        "}"
        "QPushButton#confirmBtn {"
        "   background-color: transparent;"
        "   border: 2px solid rgb(56, 142, 60);"
        "   color: rgb(56, 142, 60);"
        "   border-radius: 6px;"
        "   padding: 6px 10px;"
        "   font-weight: 700;"
        "   max-width: 90%;"
        "}"
        "QPushButton#cancelBtn {"
        "   background-color: transparent;"
        "   border: 2px solid rgb(211, 47, 47);"
        "   color: rgb(211, 47, 47);"
        "   border-radius: 6px;"
        "   padding: 6px 10px;"
        "   font-weight: 700;"
        "   max-width: 90%;"
        "}"
        "QPushButton#confirmBtn:hover,"
        "QPushButton#cancelBtn:hover {"
        "   background-color: rgba(255, 255, 255, 25);"
        "}"
    );

    addContent(content);
}