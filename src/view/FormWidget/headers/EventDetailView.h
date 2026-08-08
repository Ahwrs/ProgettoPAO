#ifndef EVENT_DETAIL_VIEW_H
#define EVENT_DETAIL_VIEW_H

#include <QWidget>
#include <QUuid>
#include "Activity.h"

// Forwarding declarations
class Event;
class Appointment;
class QVBoxLayout;

////////////////
// EventDetailView
////////////////

class EventDetailView : public QWidget {
    Q_OBJECT

private:

    QUuid activityId;
    Activity::ActivityCategory category;

    // Metodi privati
    QString detailStyle() const;
    QWidget* makeCard(const QString& header, const QString& value);
    void addCommonFields(Event* ev, QVBoxLayout* layout);
    void addButtons(QVBoxLayout* layout);

public:

    // Costruttori
    EventDetailView(Event* ev, QWidget* parent = nullptr);
    EventDetailView(Appointment* ap, QWidget* parent = nullptr);

signals:

    void editRequested(const QUuid& id);
    void deleteRequested(const QUuid& id);
    void backRequested();
};

#endif