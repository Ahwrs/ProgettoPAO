#ifndef ROW_FACTORY_H
#define ROW_FACTORY_H

#include "ActivityRow.h"
#include "TaskRow.h"
#include "EventRow.h"
#include "Task.h"
#include "Event.h"

inline ActivityRow* createRow(Activity* act, CompositeTask* parentComposite = nullptr, QWidget* parent = nullptr) {
    
    if (dynamic_cast<Task*>(act)) {

        return new TaskRow(act, parentComposite, parent);
    }
    if (dynamic_cast<Event*>(act)) {
        
        return new EventRow(act, parent);
    }
    return nullptr;
}

#endif