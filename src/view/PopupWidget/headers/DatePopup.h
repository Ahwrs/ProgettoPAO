#ifndef DATE_POPUP_H
#define DATE_POPUP_H

#include "PopupWidget.h"
#include <QCalendarWidget>

////////////////
// DatePopup
////////////////

class DatePopup : public PopupWidget {
    Q_OBJECT

public:

    DatePopup(QWidget* parent = nullptr);

signals:

    void dateSelected(QDate date);
};

#endif