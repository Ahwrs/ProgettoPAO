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
    
    virtual void update(const ActivityData& newData) override;
    virtual ActivityCategory getCategory() const override;
    virtual QJsonObject toJSON() const override;

    QString getLink() const;
    bool getIsOnline() const;
    void setLink(const QString& l);
    void setIsOnline(bool isO);
};


#endif
