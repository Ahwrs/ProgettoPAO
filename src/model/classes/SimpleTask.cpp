#include "../headers/SimpleTask.h"


SimpleTask::SimpleTask(const QString& t, const QString& d) : Task(t, d), TaskCompleted(false) {}


QString SimpleTask::getInfo() const {

    return getDescription();
}

bool SimpleTask::isCompleted() const { return TaskCompleted; }
void SimpleTask::setCompleted() { TaskCompleted = true; }