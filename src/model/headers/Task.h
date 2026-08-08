#ifndef TASK_H
#define TASK_H

#include "Activity.h"

////////////////
// Task (classe astratta)
////////////////

class Task : public Activity {

public:

    // Costruttore
    Task(const QString& t, const QString& d);
    virtual ~Task();

    // Metodo virtuale puro
    virtual bool isCompleted() const = 0;
};

#endif