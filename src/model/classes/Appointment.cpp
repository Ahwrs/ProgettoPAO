#include "Appointment.h"
#include "ActivityUtilities.h"

////////////////
// Costruttore / Distruttore
////////////////

Appointment::Appointment(const QString& title, const QString& description, 
                         const QDate& date, const QTime& start, const QTime& end,
                         const QString& link, bool isOnline) : 
                         
                         Event(title, description, date, start, end), 
                         isOnline(isOnline), 
                         link(safeURL(link)){}

////////////////
// Getter
////////////////

QString Appointment::getLink() const { return link;}
bool Appointment::getIsOnline() const { return isOnline;}

////////////////
// Setter
////////////////

void Appointment::setLink(const QString& l) { link = safeURL(l); }
void Appointment::setIsOnline(const bool isO) { isOnline = isO;}

////////////////
// Override metodi virtuali
////////////////

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

void Appointment::accept(ActivityVisitor& v) {
    
    v.visit(*this);
}

Activity::ActivityCategory Appointment::getCategory() const {
    
    return Activity::ActivityCategory::Appointment;
}