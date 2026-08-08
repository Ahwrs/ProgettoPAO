#include "ErrorPopup.h"
#include <QLabel>
#include <QPushButton>

////////////////
// Costruttore
////////////////

ErrorPopup::ErrorPopup(const QString& msg, QWidget* parent) : PopupWidget(parent){

    QWidget* content = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(content);

    QLabel* msgLabel = new QLabel(msg);
    layout->addWidget(msgLabel);

    QPushButton* okBtn = new QPushButton("OK");
    connect(okBtn, &QPushButton::clicked, this, [this]() { close();});
    layout->addWidget(okBtn, 0, Qt::AlignCenter);

    setStyleSheet(
        "ErrorPopup {"
        "   background-color: rgb(26, 12, 12);"
        "   border: 3px solid rgb(255, 49, 49);"
        "   border-radius: 6px;"
        "   padding: 5px 10px;"
        "}"
        "ErrorPopup QLabel {"
        "   color: white;"
        "   font-size: 10pt;"
        "   font-weight: 600;"
        "   font-family: Arial;"
        "   margin-bottom: 30%;"
        "}"
        "QPushButton {"
        "   background-color: transparent;"
        "   border: 2px solid rgb(56, 142, 60);"
        "   color: rgb(56, 142, 60);"
        "   border-radius: 6px;"
        "   padding: 6px 10px;"
        "   font-weight: 700;"
        "   min-width: 90%;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 25);"
        "}"
    );

    addContent(content);
}