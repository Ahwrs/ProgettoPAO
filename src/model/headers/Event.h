#ifndef EVENT_H
#define EVENT_H

#include "Activity.h"
#include <QDateTime>

class Event : public Activity {
private:
    QDate date;
    QTime startTime;
    QTime endTime;

public:
    Event(const QString& title, const QString& description,
          const QDate& date, const QTime& start, const QTime& end);
    virtual ~Event() = default;

    QString getInfo() const override;
};

#endif