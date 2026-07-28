#ifndef EVENT_ROW_H
#define EVENT_ROW_H

#include "ActivityRow.h"

class EventRow : public ActivityRow {
    Q_OBJECT

public:
    EventRow(Activity* a, QWidget* parent = nullptr);
    
};

#endif