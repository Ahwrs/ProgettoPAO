#include "ActivityManager.h"
#include "ActivityUtilities.h"
#include "Appointment.h"
#include "Event.h"
#include "SimpleTask.h"
#include "CompositeTask.h"

#include <QFile>
#include <QJsonArray>

std::unique_ptr<Activity> ActivityManager::build(const ActivityData& data){

    std::unique_ptr<Activity> newAct;
    switch(data.type){
        case Activity::ActivityCategory::Appointment:
            newAct = std::make_unique<Appointment>(data.title, data.description, data.date,
                                                     data.start, data.end, data.link, data.isOnline);
        break;
        case Activity::ActivityCategory::Event: 
            newAct = std::make_unique<Event>(data.title, data.description, data.date,
                                                data.start, data.end);
        break;
        case Activity::ActivityCategory::SimpleTask: 
            newAct = std::make_unique<SimpleTask>(data.title, data.description, data.isCompleted);

        break;
        case Activity::ActivityCategory::CompositeTask: 
                newAct = std::make_unique<CompositeTask>(data.title);
        break;

        default: return nullptr;
    }

    return newAct;
}

Activity* ActivityManager::create(const ActivityData& data){

    acty.push_back(build(data));
    return acty.back().get();   // puntatore osservatore, non owning
}

void ActivityManager::del(const QUuid& idx) {
    
    auto it = std::find_if(acty.begin(), acty.end(), [&idx](const std::unique_ptr<Activity>& a) { return a->getID() == idx; });
    if (it != acty.end()) {
        
        acty.erase(it);
        emit activitiesChanged();
        return;
    }

    // Secondo livello di delete, in caso l'attività cercata sia una SubTask.
    for (auto& a : acty) {
        if (CompositeTask* ct = dynamic_cast<CompositeTask*>(a.get())) {
            if (ct->removeTask(idx)) {

                emit activitiesChanged();
                return;
            }
        }
    }
}

void ActivityManager::edit(const QUuid& idx, const ActivityData& newData){

    auto it = std::find_if(acty.begin(), acty.end(), [&idx](const std::unique_ptr<Activity>& a) { return a->getID() == idx; });
    if(it != acty.end()){

        (*it)->update(newData);
        
    }
}

std::vector<Activity*> ActivityManager::search(const ActivityFilter& filters) const {
    
    std::vector<Activity*> result;
    for (const auto& a : acty) {
        
        if (filters.matches(a.get())) result.push_back(a.get());
    }
    return result;
}

void ActivityManager::completeSubTask(const QUuid& idx){

    for (auto& a : acty) {

        if (CompositeTask* ct = dynamic_cast<CompositeTask*>(a.get())) {

            if (ct->completeByID(idx)) {

                emit activitiesChanged();
                return;
            }
        }
    }
}

bool ActivityManager::save(const QString& path) const{

    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;

    QJsonArray arr;

    for(const std::unique_ptr<Activity>& a : acty){

        arr.append(a->toJSON());
    }

    QJsonDocument doc(arr);
    QByteArray bytes = doc.toJson();
    file.write(bytes);
    file.close();
    
    return true;
}

bool ActivityManager::load(const QString& path){
    
    std::vector<std::unique_ptr<Activity>> temp;
    
    try{
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly)) return false;

        QByteArray bytes = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(bytes);

        if(!doc.isArray()){ emit IOError("Formato JSON non valido"); return false;}
        QJsonArray arr = doc.array();

        for(const QJsonValue& obj : arr){

            std::unique_ptr<Activity> ac = build(toActivityData(obj.toObject()));
            if(CompositeTask* ct = dynamic_cast<CompositeTask*>(ac.get())){

                    QJsonArray sub = obj["SubTasks"].toArray();
                    for(const QJsonValue& val : sub){

                        ActivityData subData = toActivityData(val.toObject());
                        ct->addTask(std::make_unique<SimpleTask>(subData.title, subData.description, subData.isCompleted));
                    }
            }

            temp.push_back(std::move(ac));
        } 

        file.close();
    
    }catch(const std::invalid_argument& e){

        emit IOError(e.what()); 
        return false;
    }

    acty = std::move(temp);

    return true;
}