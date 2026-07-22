#ifndef ACTIVITY_MANAGER_H
#define ACTIVITY_MANAGER_H

#include "Activity.h"
#include "ActivityFilter.h"
#include "ActivityData.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <QObject>
#include <QDate>
#include <QTime>

class ActivityManager : public QObject{
    Q_OBJECT

private:
    std::vector<std::unique_ptr<Activity>> acty;

public:

    Activity* create(const ActivityData& data);
    void del(const QUuid& idx);
    std::vector<Activity*> search(const ActivityFilter& filters) const;
    void edit(const QUuid& idx, const ActivityData& newData);

    void save(const QString& path) const;
    void load(const QString& path);

signals:

    void activitiesChanged();
};

#endif