#ifndef EVENT_ROW_H
#define EVENT_ROW_H

#include "ActivityRow.h"
#include "Event.h"

////////////////
// EventRow (riga per visualizzazione Event/Appointment)
////////////////

class EventRow : public ActivityRow {
    Q_OBJECT

private:
    Event* event;

public:

    EventRow(Event* ev, QWidget* parent = nullptr);
    Event* getActivity() const override;

signals:
    void viewDetailsRequested(const QUuid& id);
};

#endif