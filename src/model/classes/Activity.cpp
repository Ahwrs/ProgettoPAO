#include "Activity.h"

Activity::Activity(const QString& t, const QString& d) :
    ID(QUuid::createUuid()), title(t), description(d) {}

Activity::~Activity() {}

QUuid Activity::getID() const { return ID; }
QString Activity::getTitle() const { return title; }
QString Activity::getDescription() const { return description; }

void Activity::setTitle(const QString& t) { title = t; }
void Activity::setDescription(const QString& d) { description = d; }