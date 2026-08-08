#include "ActivityManager.h"
#include "ActivityUtilities.h"
#include "Appointment.h"
#include "Event.h"
#include "SimpleTask.h"
#include "CompositeTask.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

////////////////
// Metodi privati
////////////////

std::unique_ptr<Activity> ActivityManager::build(const ActivityData& data) {

    std::unique_ptr<Activity> newAct;

    switch (data.type) {
        case Activity::ActivityCategory::Appointment:
            newAct = std::make_unique<Appointment>(data.title, data.description,
                                                    data.date, data.start, data.end,
                                                    data.link, data.isOnline );
        break;

        case Activity::ActivityCategory::Event:
            newAct = std::make_unique<Event>(data.title, data.description, 
                                            data.date, data.start, data.end);
        break;

        case Activity::ActivityCategory::SimpleTask:
            newAct = std::make_unique<SimpleTask>(data.title, data.description, data.isCompleted);
        
        break;

        case Activity::ActivityCategory::CompositeTask: {
            
            auto ct = std::make_unique<CompositeTask>(data.title);
            ct->update(data);
            
            newAct = std::move(ct);
            break;
        }

        default:
            return nullptr;
    }

    return newAct;
}

////////////////
// Operazioni CRUD
////////////////

Activity* ActivityManager::create(const ActivityData& data) {

    acty.push_back(build(data));
    emit activitiesChanged();
    return acty.back().get();
}

void ActivityManager::del(const QUuid& idx) {

    // Cerca tra le attività principali
    auto it = std::find_if(acty.begin(), acty.end(), [&idx](const std::unique_ptr<Activity>& a) { return a->getID() == idx;});

    if (it != acty.end()) {
        
        acty.erase(it);
        emit activitiesChanged();
        return;
    }

    // Cerca tra i SubTask dei CompositeTask
    for (auto& a : acty) {
        
        if (auto* ct = dynamic_cast<CompositeTask*>(a.get())) {
            
            if (ct->removeTask(idx)) {
                
                emit activitiesChanged();
                return;
            }
        }
    }
}

void ActivityManager::edit(const QUuid& idx, const ActivityData& newData) {
    
    auto it = std::find_if(acty.begin(), acty.end(), [&idx](const std::unique_ptr<Activity>& a) {return a->getID() == idx;});

    if (it != acty.end()) {
       
        (*it)->update(newData);
        emit activitiesChanged();
    }
}

////////////////
// Ricerca
////////////////

std::vector<Activity*> ActivityManager::search(const ActivityFilter& filter) const {
    
    std::vector<Activity*> result;
    for (const auto& a : acty) {
        
        if (filter.matches(a.get())) {
            
            result.push_back(a.get());
        }
    }
    return result;
}

Activity* ActivityManager::findByID(const QUuid& id) const {
    
    auto it = std::find_if(acty.begin(), acty.end(), [&id](const std::unique_ptr<Activity>& a) {return a->getID() == id;});
    return (it != acty.end()) ? it->get() : nullptr;
}

////////////////
// Completamento Task
////////////////

void ActivityManager::completeTask(const QUuid& idx) {
    
    // Cerca tra i SimpleTask principali
    auto it = std::find_if(acty.begin(), acty.end(), [&idx](const std::unique_ptr<Activity>& a) {return a->getID() == idx;});

    if (it != acty.end()) {
        
        if (auto* st = dynamic_cast<SimpleTask*>((*it).get())) {
            
            st->setCompleted();
            emit activitiesChanged();
            return;
        }
    }

    // Cerca tra i SubTask dei CompositeTask
    for (auto& a : acty) {
        
        if (auto* ct = dynamic_cast<CompositeTask*>(a.get())) {
           
            if (ct->completeByID(idx)) {
                
                emit activitiesChanged();
                return;
            }
        }
    }
}

////////////////
// Persistenza
////////////////

bool ActivityManager::save(const QString& path) const {
    
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        
        return false;
    }

    QJsonArray arr;
    for (const auto& a : acty) {
        
        // Esclude i Task completati dal salvataggio (vedere relazione)
        if (auto* t = dynamic_cast<Task*>(a.get())) {
            if (t->isCompleted()) {
                
                continue;
            }
        }
        arr.append(a->toJSON());
    }

    QJsonDocument doc(arr);
    file.write(doc.toJson());
    file.close();

    return true;
}

bool ActivityManager::load(const QString& path) {
    
    std::vector<std::unique_ptr<Activity>> temp;
    try {
        
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            
            return false;
        }

        const QByteArray bytes = file.readAll();
        const QJsonDocument doc = QJsonDocument::fromJson(bytes);

        if (!doc.isArray()) {
            
            emit IOError("Formato JSON non valido");
            return false;
        }

        const QJsonArray arr = doc.array();

        for (const QJsonValue& val : arr) {
            
            const QJsonObject obj = val.toObject();
            std::unique_ptr<Activity> ac = build(toActivityData(obj));

            // Ricostruisce i SubTask per i CompositeTask
            if (auto* ct = dynamic_cast<CompositeTask*>(ac.get())) {
                
                const QJsonArray subTasks = obj["SubTasks"].toArray();
                for (const QJsonValue& subVal : subTasks) {
                    
                    ActivityData subData = toActivityData(subVal.toObject());
                    ct->addTask(std::make_unique<SimpleTask>( subData.title, subData.description, subData.isCompleted));
                }
            }

            temp.push_back(std::move(ac));
        }

    } catch (const std::invalid_argument& e) {
        
        emit IOError(e.what());
        return false;
    }

    acty = std::move(temp);
    emit activitiesChanged();
    return true;
}