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

    void addTask(std::unique_ptr<SimpleTask> task);
    bool removeTask(const QUuid& idx);

    const std::vector<std::unique_ptr<SimpleTask>>& getSubTasks() const;
    SimpleTask* getSubTask(const QUuid& idx) const;

    virtual void update(const ActivityData& newData) override;
    virtual ActivityCategory getCategory() const override;
    virtual QJsonObject toJSON() const override;
    
    bool completeByID(const QUuid& idx);
    double getCompletionPercentage() const;
    bool isCompleted() const override;
    virtual QString getInfo() const override;
};

#endif
