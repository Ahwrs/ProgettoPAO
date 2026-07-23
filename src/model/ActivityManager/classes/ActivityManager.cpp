#include "ActivityManager.h"
#include "ActivityUtilities.h"
#include "Appointment.h"
#include "Event.h"
#include "SimpleTask.h"
#include "CompositeTask.h"

#include <QFile>
#include <QJsonArray>



Activity* ActivityManager::create(const ActivityData& data){

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
    acty.push_back(std::move(newAct));
    return acty.back().get();   // puntatore osservatore, non owning
}

void ActivityManager::del(const QUuid& idx) {
    
    auto it = std::find_if(acty.begin(), acty.end(), [&idx](const std::unique_ptr<Activity>& a) { return a->getID() == idx; });
    if (it != acty.end()) {
        acty.erase(it);
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

    try
    {
        acty.clear();
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly)) return false;

        QByteArray bytes = file.readAll();
        QJsonArray arr = QJsonDocument::fromJson(bytes).array();

        for(const QJsonValue& obj : arr){

            Activity* ac = create(toActivityData(obj.toObject()));
            if(CompositeTask* ct = dynamic_cast<CompositeTask*>(ac)){

                    QJsonArray sub = obj["SubTasks"].toArray();
                    for(const QJsonValue& val : sub){

                        ActivityData subData = toActivityData(val.toObject());
                        ct->addTask(std::make_unique<SimpleTask>(subData.title, subData.description, subData.isCompleted));
                    }
            }
        } 

        file.close();
    
    }catch(std::invalid_argument& e){

        emit IOError(e.what()); 
        return false;
    }

    return true;
}

//Chiedere se è meglio usare std::string oppure QString nella firma
void ActivityManager::IOError(const std::string& msg){

    std::cout << msg;
}