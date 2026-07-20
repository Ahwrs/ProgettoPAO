// Adattatore

#ifndef ACTIVITY_LIST_MODEL_H
#define ACTIVITY_LIST_MODEL_H

#include <QAbstractListModel>
#include <vector>
#include "Activity.h"

class ActivityListModel : public QAbstractListModel {
    Q_OBJECT

private:

    std::vector<Activity*>* dataSource;  // Non-Owning: La ownership resta al Controller

public:

    enum ActivityRoles {

        ActivityPointerRole = Qt::UserRole + 1
    };

    ActivityListModel(std::vector<Activity*>* source, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void addActivity(Activity* activity);
    void removeActivity(int row);
    void refresh();

};

Q_DECLARE_METATYPE(Activity*)

#endif