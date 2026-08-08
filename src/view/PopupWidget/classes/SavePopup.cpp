#include "SavePopup.h"
#include <QPushButton>

////////////////
// Costruttore
////////////////

SavePopup::SavePopup(bool hasCurrentFile, QWidget* parent) : PopupWidget(parent){

    QWidget* content = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(content);

    QPushButton* saveBtn = new QPushButton("Salva");
    saveBtn->setEnabled(hasCurrentFile);

    QPushButton* saveAsBtn = new QPushButton("Salva con nome...");

    layout->addWidget(saveBtn);
    layout->addSpacing(5);
    layout->addWidget(saveAsBtn);
    addContent(content);

    connect(saveBtn, &QPushButton::clicked, this, [this]() {

        close();
        emit saveRequested();
    });

    connect(saveAsBtn, &QPushButton::clicked, this, [this]() {
        
        close();
        emit saveAsRequested();
    });

    setStyleSheet(
        "SavePopup {"
        "   background-color: rgb(14, 34, 14);"
        "   border: 3px solid rgb(64, 255, 128);"
        "   border-radius: 6px;"
        "   padding: 5px 10px;"
        "}"
        "SavePopup QWidget {"
        "   background-color: transparent;"
        "   margin: 0px;"
        "}"
        "QPushButton {"
        "   background-color: transparent;"
        "   border: 2px solid #E9ECEF;"
        "   color: #E9ECEF;"
        "   border-radius: 6px;"
        "   padding: 6px 10px;"
        "   font-weight: 700;"
        "}"
        "QPushButton:pressed, QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 25);"
        "}"
    );
}