#include "CompositeTask.h"

#include <utility>

CompositeTask::CompositeTask(const QString& title) : Task(title, QString()) {}

void CompositeTask::addTask(std::unique_ptr<Task> task) {
    
    if (task) SubTasks.push_back(std::move(task));
}

void CompositeTask::removeTask(int index) {

    if (index >= 0 && index < static_cast<int>(SubTasks.size())) {

        SubTasks.erase(SubTasks.begin() + index);
    }
}

double CompositeTask::getCompletionPercentage() const {
    
    double completedCount = 0.0;
    
    for (const std::unique_ptr<Task>& t : SubTasks) {
        
        if (t->isCompleted()) completedCount++;
    }
    return SubTasks.size() <= 0 ? 0.0 : (completedCount / SubTasks.size()) * 100.0;
}

bool CompositeTask::isCompleted() const {return getCompletionPercentage() == 100.0; }

QString CompositeTask::getInfo() const {
    
    QString result = "";
    
    if (SubTasks.empty()) {
    
        result += "(nessuna sotto-attività)\n";
    
    } else {
    
        result += "Sub-Task:\n";
    
        for (const std::unique_ptr<Task>& t : SubTasks) {
            
            
            QString childInfo = t->getInfo();
            result += "\n"+childInfo;           
            
        }
    }
    return result;
}

Activity::ActivityCategory CompositeTask::getCategory() const {return Activity::CompositeTask;}
