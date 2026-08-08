#include "CompositeTask.h"
#include <utility>
#include <QJsonArray>

////////////////
// Costruttore
////////////////

CompositeTask::CompositeTask(const QString& title) : Task(title, QString()){}

////////////////
// Gestione SubTask
////////////////

void CompositeTask::addTask(std::unique_ptr<SimpleTask> task) {
    
    if (task) {
        SubTasks.push_back(std::move(task));
    }
}

bool CompositeTask::removeTask(const QUuid& idx) {
    
    auto it = std::find_if(SubTasks.begin(), SubTasks.end(), [&idx](const std::unique_ptr<SimpleTask>& st) { return st->getID() == idx; });

    if (it == SubTasks.end()) {
        return false;
    }
    
    SubTasks.erase(it);
    return true;
}

bool CompositeTask::completeByID(const QUuid& idx) {
    
    auto it = std::find_if(SubTasks.begin(), SubTasks.end(), [&idx](const std::unique_ptr<SimpleTask>& st) { return st->getID() == idx; });

    if (it == SubTasks.end()) {
        return false;
    }

    (*it)->setCompleted();
    return true;
}

const std::vector<std::unique_ptr<SimpleTask>>& CompositeTask::getSubTasks() const {
    
    return SubTasks;
}

SimpleTask* CompositeTask::getSubTask(const QUuid& idx) const {
    
    auto it = std::find_if(SubTasks.begin(), SubTasks.end(), [&idx](const std::unique_ptr<SimpleTask>& st) { return st->getID() == idx;});
    return (it != SubTasks.end()) ? it->get() : nullptr;
}

////////////////
// Info e stato
////////////////

double CompositeTask::getCompletionPercentage() const {
    
    if (SubTasks.empty()) {
        return 0.0;
    }

    double completedCount = 0.0;
    
    for (const auto& t : SubTasks) {
        
        if (t->isCompleted()) {
            completedCount++;
        }
    }
    return (completedCount / SubTasks.size()) * 100.0;
}

bool CompositeTask::isCompleted() const { return getCompletionPercentage() == 100.0;}


////////////////
// Override metodi virtuali (Activity/Task)
////////////////

void CompositeTask::update(const ActivityData& newData) {
    
    setTitle(newData.title);
    syncSubTasks(newData.subTasks);
}

QJsonObject CompositeTask::toJSON() const {
    
    QJsonObject obj = Activity::toJSON();

    QJsonArray arr;
    for (const auto& s : SubTasks) {
        arr.append(s->toJSON());
    }

    obj["SubTasks"] = arr;
    obj["CategoryType"] = CatToString(getCategory());

    return obj;
}

void CompositeTask::accept(ActivityVisitor& v) {
    
    v.visit(*this);
}

Activity::ActivityCategory CompositeTask::getCategory() const {
    
    return Activity::ActivityCategory::CompositeTask;
}

////////////////
// Metodi privati
////////////////

void CompositeTask::syncSubTasks(const std::vector<SubTaskData>& entries) {
    
    // Rimuovi i SubTask non presenti in entries
    std::vector<QUuid> idsToRemove;
    for (const auto& s : SubTasks) {
        
        auto it = std::find_if(entries.begin(), entries.end(), [&](const SubTaskData& e) { return e.id == s->getID(); });
        if (it == entries.end()) {
            
            idsToRemove.push_back(s->getID());
        }
    }
    
    for (const QUuid& id : idsToRemove) {
        
        removeTask(id);
    }

    // Aggiorna o aggiungi i SubTask da entries
    for (const auto& t : entries) {
        
        if (!t.id.isNull()) {
            
            if (SimpleTask* st = getSubTask(t.id)) {
                
                st->setTitle(t.title);
                st->setDescription(t.description);
            }
        } 
        else {
            
            addTask(std::make_unique<SimpleTask>(t.title, t.description));
        }
    }
}