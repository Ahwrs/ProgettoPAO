#include "EventRow.h"

////////////////
// Costruttore
////////////////

EventRow::EventRow(Event* ev, QWidget* parent) : ActivityRow(ev, parent), event(ev) {

    // All'espansione della riga, emette il segnale per visualizzare i dettagli
    connect(this, &ActivityRow::contentToggled, this, [this]() {

        emit viewDetailsRequested(act->getID());
    });
}

////////////////
// Getter
////////////////

Event* EventRow::getActivity() const {
    return event;
}