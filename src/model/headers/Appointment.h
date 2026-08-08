#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Event.h"

////////////////
// Appointment
////////////////

class Appointment : public Event {

private:
    bool isOnline;
    QString link;

public:

    // Costruttore / distruttore
    Appointment(const QString& title, const QString& description,
                const QDate& date, const QTime& start, const QTime& end,
                const QString& link, bool isOnline);
    
    virtual ~Appointment() = default;

    // Override metodi virtuali
    virtual void accept(ActivityVisitor& v) override;
    virtual void update(const ActivityData& newData) override;
    virtual QJsonObject toJSON() const override;
    virtual ActivityCategory getCategory() const override;

    // Getter
    QString getLink() const;
    bool getIsOnline() const;

    // Setter
    void setLink(const QString& l);
    void setIsOnline(bool isO);
};

#endif