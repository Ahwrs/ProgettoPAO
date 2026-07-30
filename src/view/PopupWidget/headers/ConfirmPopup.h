#ifndef CONFIRM_POPUP_H
#define CONFIRM_POPUP_H

#include "PopupWidget.h"

class ConfirmPopup : public PopupWidget {
    Q_OBJECT

public:
    ConfirmPopup(const QString& message, QWidget* parent = nullptr);

signals:
    void confirmed();
    void cancelled();
};

#endif