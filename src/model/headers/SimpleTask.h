#ifndef SIMPLE_TASK_H
#define SIMPLE_TASK_H

#include "Task.h"

class SimpleTask : public Task{

private:

    bool TaskCompleted;

public:

    SimpleTask(const QString& t, const QString& d);
    ~SimpleTask() = default;

    QString getInfo() const override;
    bool isCompleted() const override;
    void setCompleted();
};

#endif