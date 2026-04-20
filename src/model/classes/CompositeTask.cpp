#include "../headers/CompositeTask.h"

CompositeTask::CompositeTask(const QString& title) : Task(title, QString()) {}
CompositeTask::~CompositeTask() {

    for (Task* t : SubTasks)
        
        delete t;
}

void CompositeTask::addTask(Task* task) {
    
    if (task)
        
        SubTasks.push_back(task);
}

void CompositeTask::removeTask(int index) {

    if (index >= 0 && index < static_cast<int>(SubTasks.size())) {

        delete SubTasks[index];
        SubTasks.erase(SubTasks.begin() + index);
    }
}

double CompositeTask::getCompletionPercentage() const {
    
    double completedCount = 0.0;
    
    for (const Task* t : SubTasks) {
        
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
    
        for (const Task* t : SubTasks) {
            
            
            QString childInfo = t->getInfo();
            result += "\n"+childInfo;           
            
        }
    }
    return result;
}