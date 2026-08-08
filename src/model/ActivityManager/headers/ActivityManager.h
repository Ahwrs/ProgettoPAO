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

////////////////
// ActivityManager
////////////////

class ActivityManager : public QObject {
    Q_OBJECT

private:

    std::vector<std::unique_ptr<Activity>> acty;

    std::unique_ptr<Activity> build(const ActivityData& data);

public:

    // Operazioni CRUD
    Activity* create(const ActivityData& data);
    void del(const QUuid& idx);
    void edit(const QUuid& idx, const ActivityData& newData);

    // Ricerca
    std::vector<Activity*> search(const ActivityFilter& filter) const;
    Activity* findByID(const QUuid& id) const;

    // Completamento Task
    void completeTask(const QUuid& idx);

    // Persistenza
    bool save(const QString& path) const;
    bool load(const QString& path);

signals:

    void activitiesChanged();
    void IOError(const QString& msg);
};

#endif