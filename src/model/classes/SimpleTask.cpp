#include "SimpleTask.h"
#include "ActivityUtilities.h"

////////////////
// Costruttore
////////////////

SimpleTask::SimpleTask(const QString& t, const QString& d, bool Tc): Task(t, d), TaskCompleted(Tc){}

////////////////
// Stato completamento
////////////////

bool SimpleTask::isCompleted() const { return TaskCompleted; }
void SimpleTask::setCompleted() { TaskCompleted = true;}

////////////////
// Override metodi virtuali
////////////////

QJsonObject SimpleTask::toJSON() const {

    QJsonObject obj = Activity::toJSON();
    obj["Completed"] = isCompleted();
    obj["CategoryType"] = CatToString(getCategory());
    return obj;
}

void SimpleTask::accept(ActivityVisitor& v) { v.visit(*this);}
Activity::ActivityCategory SimpleTask::getCategory() const {
    
    return Activity::ActivityCategory::SimpleTask;
}