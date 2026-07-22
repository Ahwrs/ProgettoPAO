#include "ActivityManager.h"
#include "ActivityData.h"
#include "Appointment.h"
#include "Event.h"
#include "SimpleTask.h"
#include "CompositeTask.h"

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
            newAct = std::make_unique<SimpleTask>(data.title, data.description);

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