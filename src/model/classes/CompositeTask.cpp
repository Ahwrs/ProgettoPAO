#include "CompositeTask.h"
#include "ActivityUtilities.h"

#include <utility>
#include <QJsonArray>

CompositeTask::CompositeTask(const QString& title) : Task(title, QString()) {}

void CompositeTask::addTask(std::unique_ptr<SimpleTask> task) {
    
    if (task) SubTasks.push_back(std::move(task));
}

bool CompositeTask::removeTask(const QUuid& idx) {

    auto it = std::find_if(SubTasks.begin(), SubTasks.end(),
        [&idx](const std::unique_ptr<SimpleTask>& st) { return st->getID() == idx; });
    
    if (it == SubTasks.end()) return false;
    SubTasks.erase(it);
    
    return true;
}

bool CompositeTask::completeByID(const QUuid& idx) {
    
    auto it = std::find_if(SubTasks.begin(), SubTasks.end(),
        [&idx](const std::unique_ptr<SimpleTask>& st) { return st->getID() == idx; });
    
    if (it == SubTasks.end()) return false;
    (*it)->setCompleted();

    return true;
}

double CompositeTask::getCompletionPercentage() const {
    
    double completedCount = 0.0;
    
    for (const std::unique_ptr<SimpleTask>& t : SubTasks) {
        
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
    
        for (const std::unique_ptr<SimpleTask>& t : SubTasks) {
            
            
            QString childInfo = t->getInfo();
            result += "\n"+childInfo;           
            
        }
    }
    return result;
}

const std::vector<std::unique_ptr<SimpleTask>>& CompositeTask::getSubTasks() const { return SubTasks; }

SimpleTask* CompositeTask::getSubTask(const QUuid& idx) const {

    auto it = std::find_if(SubTasks.begin(), SubTasks.end(), [&idx](const std::unique_ptr<SimpleTask>& st) { return st->getID() == idx; });
    if(it != SubTasks.end()){

        return (*it).get();
    }

    return nullptr;
}

void CompositeTask::update(const ActivityData& newData) {
    
    setTitle(newData.title);
}

QJsonObject CompositeTask::toJSON() const {

    QJsonObject obj = Activity::toJSON();

    QJsonArray arr;
    for(const std::unique_ptr<SimpleTask>& s : SubTasks){

        arr.append(s->toJSON());
    }

    obj["SubTasks"] = arr;
    obj["CategoryType"] = CatToString(getCategory());

    return obj;
}

Activity::ActivityCategory CompositeTask::getCategory() const {return Activity::ActivityCategory::CompositeTask;}
