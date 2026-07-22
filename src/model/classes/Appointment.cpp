#include "Appointment.h"
#include "ActivityData.h"

Appointment::Appointment(const QString& title, const QString& description,
                const QDate& date, const QTime& start, const QTime& end,
                const QString& link, bool isOnline) :

                Event(title, description, date, start, end),
                isOnline(isOnline), link(link) {}

QString Appointment::getLink() const { return link; }
bool Appointment::getIsOnline() const { return isOnline; }
QString Appointment::getInfo() const {

    return Event::getInfo() + (isOnline ? "\nMeeting: " : "\nLocation: ") + link;
}
void Appointment::setLink(const QString& l) { link = l;}
void Appointment::setIsOnline(const bool isO) { isOnline = isO;}

void Appointment::update(const ActivityData& newData) { 

    Event::update(newData);
    setLink(newData.link);
    setIsOnline(newData.isOnline);
}

Activity::ActivityCategory Appointment::getCategory() const {return Activity::ActivityCategory::Appointment;}
