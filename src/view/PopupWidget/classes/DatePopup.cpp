#include "DatePopup.h"
#include <QVBoxLayout>
#include <QTextCharFormat>
#include <QToolButton>
#include <QSpinBox>

////////////////
// Costruttore
////////////////

DatePopup::DatePopup(QWidget* parent) : PopupWidget(parent) {

    QWidget* content = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(content);

    QCalendarWidget* calendar = new QCalendarWidget();
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // Formattazione weekend
    QTextCharFormat weekendFormat = QTextCharFormat();
    weekendFormat.setForeground(QColor("#38BDF8"));
    calendar->setWeekdayTextFormat(Qt::Saturday, weekendFormat);
    calendar->setWeekdayTextFormat(Qt::Sunday, weekendFormat);

    // Icone navigazione
    if (auto* leftBtn = calendar->findChild<QToolButton*>("qt_calendar_prevmonth")) {
        
        leftBtn->setIcon(QIcon(":/Left.svg"));
    }
    if (auto* rightBtn = calendar->findChild<QToolButton*>("qt_calendar_nextmonth")) {

        rightBtn->setIcon(QIcon(":/Right.svg"));
    }

    // Style calendario
    calendar->setStyleSheet(

        "QCalendarWidget {"
        "   background-color: transparent;"
        "   color: white;"
        "}"
        "QCalendarWidget QToolButton {"
        "   color: white;"
        "   background-color: transparent;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "   font-weight: 600;"
        "}"
        "QCalendarWidget QToolButton:hover {"
        "   background-color: rgba(255,255,255,15);"
        "}"
        "QCalendarWidget QToolButton::menu-indicator {"
        "   image: none;"
        "}"
        "QCalendarWidget QSpinBox {"
        "   width: 25px;"
        "   color: black;"
        "}"
        "QCalendarWidget QWidget#qt_calendar_navigationbar {"
        "   background-color: rgb(20,23,28);"
        "}"
        "QCalendarWidget QAbstractItemView:enabled {"
        "   color: white;"
        "   background-color: rgb(15,17,21);"
        "   outline: none;"
        "}"
        "QCalendarWidget QAbstractItemView:disabled {"
        "   color: rgba(255,255,255,60);"
        "}"
    );

    layout->addWidget(calendar);
    addContent(content);

    // Connessione selezione data
    connect(calendar, &QCalendarWidget::clicked, this, [this](const QDate& date) {
        
        emit dateSelected(date);
        close();
    });
}