#include "../headers/Appointment.h"

Appointment::Appointment(const QString& title, const QString& description,
                const QDate& date, const QTime& start, const QTime& end,
                const QString& link, bool isOnline) :

                Event(title, description, date, start, end),
                link(link), isOnline(isOnline) {}

QString Appointment::getLink() const { return link; }
QString Appointment::getInfo() const {

    return Event::getInfo() + (isOnline ? "\nMeeting: " : "\nLocation: ") + link;
}