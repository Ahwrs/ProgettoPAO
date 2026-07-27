#ifndef ACTIVITY_MANAGER_H
#define ACTIVITY_MANAGER_H

#include "Activity.h"
#include "ActivityFilter.h"
#include "ActivityUtilities.h"
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

    std::unique_ptr<Activity> build(const ActivityData& data);

public:

    Activity* create(const ActivityData& data);
    void del(const QUuid& idx);
    std::vector<Activity*> search(const ActivityFilter& filters) const;
    void edit(const QUuid& idx, const ActivityData& newData);
    void completeSubTask(const QUuid& idx);

    bool save(const QString& path) const;
    bool load(const QString& path);

signals:

    void activitiesChanged();
    void IOError(const QString& msg);
};

#endif