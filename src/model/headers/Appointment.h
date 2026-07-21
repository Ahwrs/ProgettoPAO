#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Event.h"

class Appointment : public Event{

private:

    bool isOnline;
    QString link;

public:

    Appointment(const QString& title, const QString& description,
                const QDate& date, const QTime& start, const QTime& end,
                const QString& link, bool isOnline);
    virtual ~Appointment() = default;

    QString getInfo() const override;
    QString getLink() const;
};


#endif