#ifndef SIMPLE_TASK_H
#define SIMPLE_TASK_H

#include "Task.h"

class SimpleTask : public Task{

private:

    bool TaskCompleted;

public:

    SimpleTask(const QString& t, const QString& d, bool Tc = false);
    ~SimpleTask() = default;

    virtual QString getInfo() const override;
    virtual ActivityCategory getCategory() const override;

    virtual QJsonObject toJSON() const override;
    

    bool isCompleted() const override;
    void setCompleted();
};

#endif