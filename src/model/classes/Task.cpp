#include "Task.h"

////////////////
// Costruttore / Distruttore
////////////////

Task::Task(const QString& t, const QString& d) : Activity(t, d){}
Task::~Task() = default;