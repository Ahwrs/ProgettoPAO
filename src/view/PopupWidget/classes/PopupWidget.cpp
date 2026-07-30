#include "PopupWidget.h"

PopupWidget::PopupWidget(QWidget* p) : QWidget(p) {

    setAttribute(Qt::WA_StyledBackground, true);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(Qt::Popup);
    box = new QVBoxLayout(this);

    setStyleSheet(
        "PopupWidget {"
        "   background-color: rgb(26, 12, 12);"
        "   border: 2px solid rgb(255, 49, 49);"
        "   border-radius: 6px;"
        "   padding: 5px 10px;"
        "}"
        "PopupWidget QLabel {"
        "   color: white;"
        "   font-size: 10pt;"
        "   margin-bottom: 30%;"
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
        "QPushButton#confirmBtn:hover, QPushButton#cancelBtn:hover { background-color: rgba(255, 255, 255, 25); }"
    );
}

void PopupWidget::showCenteredTop(QWidget* mainWidget, int topMargin) {

    QWidget* topLevel = mainWidget->window();   


    QPoint windowOrigin = topLevel->mapToGlobal(QPoint(0, 0));
    adjustSize();   

    int x = windowOrigin.x() + (topLevel->width() - width()) / 2;
    int y = windowOrigin.y() + topMargin;

    move(x, y);
    show();
}

void PopupWidget::addContent(QWidget* c) { box->addWidget(c); }