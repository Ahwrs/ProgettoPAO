#ifndef COMPOSITE_TASK_H
#define COMPOSITE_TASK_H

#include "Task.h"
#include <memory>
#include <vector>

class CompositeTask : public Task {
private:
    std::vector<std::unique_ptr<Task>> SubTasks;

public:
    CompositeTask(const QString& title);
    ~CompositeTask() override = default;

    CompositeTask(const CompositeTask&) = delete;
    CompositeTask& operator=(const CompositeTask&) = delete;

    void addTask(std::unique_ptr<Task> task);
    void removeTask(int index);
    double getCompletionPercentage() const;

    bool isCompleted() const override;
    QString getInfo() const override;
};

#endif
