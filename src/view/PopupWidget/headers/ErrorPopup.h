#ifndef ERROR_POPUP_H
#define ERROR_POPUP_H

#include "PopupWidget.h"

////////////////
// ErrorPopup
////////////////

class ErrorPopup : public PopupWidget {
    Q_OBJECT

public:
    ErrorPopup(const QString& message, QWidget* parent = nullptr);
};

#endif