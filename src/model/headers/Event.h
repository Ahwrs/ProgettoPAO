#ifndef EVENT_H
#define EVENT_H

#include "Activity.h"
#include <QDate>
#include <QTime>

////////////////
// Event
////////////////

class Event : public Activity {

private:
    QDate date;
    QTime startTime;
    QTime endTime;

public:

    // Costruttore
    Event(const QString& title, const QString& description,
          const QDate& date, const QTime& start, const QTime& end);
    
    virtual ~Event() = default;

    // Override metodi virtuali
    void update(const ActivityData& newData) override;
    void accept(ActivityVisitor& v) override;
    QJsonObject toJSON() const override;
    ActivityCategory getCategory() const override;

    // Getter
    QDate getDate() const;
    QTime getStartTime() const;
    QTime getEndTime() const;

    // Setter
    void setDate(const QDate& d);
    void setStartTime(const QTime& s);
    void setEndTime(const QTime& e);
};

#endif