#ifndef COMPOSITE_TASK_H
#define COMPOSITE_TASK_H

#include "Task.h"
#include <vector>

class CompositeTask : public Task {
private:
    std::vector<Task*> SubTasks;  

public:
    CompositeTask(const QString& title);
    ~CompositeTask();  

    void addTask(Task* task);          
    void removeTask(int index);
    double getCompletionPercentage() const;

    bool isCompleted() const override;
    QString getInfo() const override;
};

#endif