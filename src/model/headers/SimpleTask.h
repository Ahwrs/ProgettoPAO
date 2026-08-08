#ifndef SIMPLE_TASK_H
#define SIMPLE_TASK_H

#include "Task.h"

////////////////
// SimpleTask
////////////////

class SimpleTask : public Task {

private:
    bool TaskCompleted;

public:

    // Costruttore
    SimpleTask(const QString& t, const QString& d, bool Tc = false);
    ~SimpleTask() = default;

    // Override metodi virtuali
    void accept(ActivityVisitor& v) override;
    QJsonObject toJSON() const override;
    ActivityCategory getCategory() const override;

    // Stato completamento
    bool isCompleted() const override;
    void setCompleted();
};

#endif