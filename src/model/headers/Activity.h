#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QUuid>
#include <QJsonObject>

// Forward declarations
struct ActivityData;
class Event;
class SimpleTask;
class CompositeTask;
class Appointment;

////////////////
// ActivityVisitor
////////////////

class ActivityVisitor {
public:
    virtual ~ActivityVisitor() = default;

    virtual void visit(SimpleTask&) = 0;
    virtual void visit(CompositeTask&) = 0;
    virtual void visit(Event&) = 0;
    virtual void visit(Appointment&) = 0;
};

////////////////
// Activity (classe base astratta)
////////////////

class Activity {

private:
    const QUuid ID;
    QString title;
    QString description;

public:

    // Tipi di attività
    enum class ActivityCategory {
        Event,
        SimpleTask,
        CompositeTask,
        Appointment
    };

    // Costruttore / distruttore
    Activity(const QString& t, const QString& d);
    virtual ~Activity();

    // Copia disabilitata
    Activity(const Activity&) = delete;
    Activity& operator=(const Activity&) = delete;

    // Metodi virtuali puri
    virtual void accept(ActivityVisitor& v) = 0;
    virtual ActivityCategory getCategory() const = 0;

    // Metodi virtuali con codice base
    virtual void update(const ActivityData& newData);
    virtual QJsonObject toJSON() const;

    // Getter
    QUuid getID() const;
    QString getTitle() const;
    QString getDescription() const;

    // Setter
    void setTitle(const QString& t);
    void setDescription(const QString& d);
};

#endif