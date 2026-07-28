#include "Appointment.h"
#include "ActivityUtilities.h"

Appointment::Appointment(const QString& title, const QString& description,
                const QDate& date, const QTime& start, const QTime& end,
                const QString& link, bool isOnline) :

                Event(title, description, date, start, end),
                isOnline(isOnline), link(safeURL(link)) {}

QString Appointment::getLink() const { return link; }
bool Appointment::getIsOnline() const { return isOnline; }

void Appointment::setLink(const QString& l) { link = safeURL(l);}
void Appointment::setIsOnline(const bool isO) { isOnline = isO;}

void Appointment::update(const ActivityData& newData) { 

    Event::update(newData);
    setLink(newData.link);
    setIsOnline(newData.isOnline);
}

QJsonObject Appointment::toJSON() const {

    QJsonObject obj = Event::toJSON();
    obj["Link"] = getLink();
    obj["Online"] = getIsOnline();
    obj["CategoryType"] = CatToString(getCategory());

    return obj;
}

Activity::ActivityCategory Appointment::getCategory() const {return Activity::ActivityCategory::Appointment;}
