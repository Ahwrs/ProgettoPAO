#include "Activity.h"
#include "ActivityUtilities.h"

Activity::Activity(const QString& t, const QString& d) :
    ID(QUuid::createUuid()), title(t), description(d) {}

Activity::~Activity() {}

QUuid Activity::getID() const { return ID; }
QString Activity::getTitle() const { return title; }
QString Activity::getDescription() const { return description; }

void Activity::update(const ActivityData& newData){

    setTitle(newData.title);
    setDescription(newData.description);
}

QJsonObject Activity::toJSON() const {

    QJsonObject obj;
    obj["ID"] = getID().toString();
    obj["Title"] = getTitle();
    obj["Description"] = getDescription();

    return obj;
}

void Activity::setTitle(const QString& t) { title = t; }
void Activity::setDescription(const QString& d) { description = d; }