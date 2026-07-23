#include "SimpleTask.h"
#include "ActivityUtilities.h"


SimpleTask::SimpleTask(const QString& t, const QString& d, bool Tc) : Task(t, d), TaskCompleted(Tc) {}


QString SimpleTask::getInfo() const {

    return getDescription();
}

QJsonObject SimpleTask::toJSON() const {

    QJsonObject obj = Activity::toJSON();
    obj["Completed"] = isCompleted();
    obj["CategoryType"] = CatToString(getCategory());

    return obj;
}

bool SimpleTask::isCompleted() const { return TaskCompleted; }
void SimpleTask::setCompleted() { TaskCompleted = true; }
Activity::ActivityCategory SimpleTask::getCategory() const {return Activity::ActivityCategory::SimpleTask;}