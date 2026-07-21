#ifndef ACTIVITY_MANAGER_H
#define ACTIVITY_MANAGER_H

#include "Activity.h"
#include "ActivityFilter.h"
#include <vector>
#include <memory>
#include <QObject>
#include <QDate>
#include <QTime>

struct ActivityData{

    Activity::ActivityCategory type;
    QString title;
    QString description;

    QDate date;
    QTime start, end;

    QString link;
    bool isOnline = false;
};

class ActivityManager : public QObject{
    Q_OBJECT

private:
    std::vector<std::unique_ptr<Activity>> activities;

public:

    Activity* create(const ActivityData& data);
    void del(const QUuid& idx);
    std::vector<Activity*> search(const ActivityFilter& filters) const;
    virtual void edit() const;

    void save(const QString& path) const;
    void load(const QString& path);

};

class EventManager : public ActivityManager{
    
public:

    virtual Activity* create(const QString& t, const QString& d, 
                            const QTime s, const QTime e, const QDate dt);
    
    
};

class SimpleTManager : public ActivityManager{
    
public:

    virtual Activity* create(const QString& t, const QString& d, const bool isComp);
    
};

#endif