#ifndef TASK_H
#define TASK_H

#include "Activity.h"

class Task : public Activity{

public:

    Task(const QString& t, const QString& d);
    virtual ~Task();

    virtual bool isCompleted() const = 0;
};


#endif