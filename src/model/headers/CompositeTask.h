#ifndef COMPOSITE_TASK_H
#define COMPOSITE_TASK_H

#include "Task.h"
#include "SimpleTask.h"
#include <memory>
#include <vector>

class CompositeTask : public Task {
private:

    std::vector<std::unique_ptr<SimpleTask>> SubTasks;

public:
    CompositeTask(const QString& title);
    ~CompositeTask() override = default;

    CompositeTask(const CompositeTask&) = delete;
    CompositeTask& operator=(const CompositeTask&) = delete;

    void addTask(std::unique_ptr<SimpleTask> task);
    void removeTask(int index);

    const std::vector<std::unique_ptr<SimpleTask>>& getSubTasks() const;
    SimpleTask* getSubTask(int index) const;

    void update(const ActivityData& newData) override;

    double getCompletionPercentage() const;
    bool isCompleted() const override;
    QString getInfo() const override;
    ActivityCategory getCategory() const override;
};

#endif
