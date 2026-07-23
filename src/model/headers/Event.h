#ifndef EVENT_H
#define EVENT_H

#include "Activity.h"
#include <QDate>
#include <QTime>

class Event : public Activity {
private:
    QDate date;
    QTime startTime;
    QTime endTime;

public:
    Event(const QString& title, const QString& description,
          const QDate& date, const QTime& start, const QTime& end);
    virtual ~Event() = default;

    virtual QString getInfo() const override;

    virtual void update(const ActivityData& newData) override;
    virtual ActivityCategory getCategory() const override;
    virtual QJsonObject toJSON() const override;
    

    QDate getDate() const;
    QTime getStartTime() const;
    QTime getEndTime() const;

    void setDate(const QDate& d);
    void setStartTime(const QTime& s);
    void setEndTime(const QTime& e);
};

#endif