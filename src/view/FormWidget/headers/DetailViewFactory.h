#ifndef DETAIL_VIEW_FACTORY_H
#define DETAIL_VIEW_FACTORY_H

#include "EventDetailView.h"
#include "Activity.h"
#include "Event.h"
#include "Appointment.h"
#include "SimpleTask.h"
#include "CompositeTask.h"

////////////////
// DetailViewFactoryVisitor
////////////////

class DetailViewFactoryVisitor : public ActivityVisitor {

public:

    EventDetailView* result = nullptr;

    void visit(SimpleTask&) override {}
    void visit(CompositeTask&) override {}
    void visit(Event& e) override {

        result = new EventDetailView(&e);
    }
    void visit(Appointment& a) override {

        result = new EventDetailView(&a);
    }
};

////////////////
// Funzione factory
////////////////

inline EventDetailView* createDetailView(Activity* act) {
    
    DetailViewFactoryVisitor visitor;
    act->accept(visitor);
    return visitor.result;
}

#endif