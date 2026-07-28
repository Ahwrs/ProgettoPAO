#include "Event.h"
#include "ActivityUtilities.h"

Event::Event(const QString& title, const QString& description,
          const QDate& date, const QTime& start, const QTime& end) : Activity(title, description), date(date), startTime(start), endTime(end) {}


QDate Event::getDate() const { return date; }
QTime Event::getStartTime() const { return startTime; }
QTime Event::getEndTime() const { return endTime; }

void Event::setDate(const QDate& d) { date = d; }
void Event::setStartTime(const QTime& s) { startTime = s; }
void Event::setEndTime(const QTime& e) { endTime = e; }

void Event::update(const ActivityData& newData) {

    Activity::update(newData);
    setDate(newData.date);
    setStartTime(newData.start);
    setEndTime(newData.end);
}

QJsonObject Event::toJSON() const {

    QJsonObject obj = Activity::toJSON();
    obj["Date"] = getDate().toString(Qt::ISODate);
    obj["StartTime"] = getStartTime().toString(Qt::ISODate);
    obj["EndTime"] = getEndTime().toString(Qt::ISODate);
    obj["CategoryType"] = CatToString(getCategory());

    return obj;
}

Activity::ActivityCategory Event::getCategory() const {return Activity::ActivityCategory::Event;}