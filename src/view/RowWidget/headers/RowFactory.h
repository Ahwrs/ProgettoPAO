#ifndef ROW_FACTORY_H
#define ROW_FACTORY_H

#include "ActivityRow.h"
#include "TaskRow.h"
#include "EventRow.h"
#include "Activity.h"
#include "Appointment.h"

////////////////
// RowFactoryVisitor (visitor per creare righe)
////////////////

class RowFactoryVisitor : public ActivityVisitor {
public:

    ActivityRow* result = nullptr;

    void visit(SimpleTask& t) override { result = new TaskRow(&t); }
    void visit(CompositeTask& t) override { result = new TaskRow(&t); }
    void visit(Event& e) override { result = new EventRow(&e); }
    void visit(Appointment& a) override { result = new EventRow(&a); }
};

////////////////
// Funzione factory
////////////////

inline ActivityRow* createRow(Activity* act) {
    
    RowFactoryVisitor visitor;
    act->accept(visitor);
    return visitor.result;
}

#endif