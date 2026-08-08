#ifndef SAVE_POPUP_H
#define SAVE_POPUP_H

#include "PopupWidget.h"

////////////////
// SavePopup
////////////////

class SavePopup : public PopupWidget {
    Q_OBJECT

public:
    SavePopup(bool hasCurrentFile, QWidget* parent = nullptr);

signals:
    void saveRequested();
    void saveAsRequested();
};

#endif