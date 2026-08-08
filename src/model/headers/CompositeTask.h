#ifndef COMPOSITE_TASK_H
#define COMPOSITE_TASK_H

#include "Task.h"
#include "SimpleTask.h"
#include "ActivityUtilities.h"
#include <memory>
#include <vector>

////////////////
// CompositeTask
////////////////

class CompositeTask : public Task {

private:

    std::vector<std::unique_ptr<SimpleTask>> SubTasks;

    void syncSubTasks(const std::vector<SubTaskData>& entries);

public:

    // Costruttore/Distruttore
    CompositeTask(const QString& title);
    ~CompositeTask() override = default;

    // Gestione SubTask
    void addTask(std::unique_ptr<SimpleTask> task);
    bool removeTask(const QUuid& idx);
    bool completeByID(const QUuid& idx);

    const std::vector<std::unique_ptr<SimpleTask>>& getSubTasks() const;
    SimpleTask* getSubTask(const QUuid& idx) const;

    // Info e stato
    double getCompletionPercentage() const;
    bool isCompleted() const override;

    // Override metodi virtuali (Activity/Task)
    void update(const ActivityData& newData) override;
    QJsonObject toJSON() const override;
    void accept(ActivityVisitor& v) override;
    ActivityCategory getCategory() const override;
};

#endif