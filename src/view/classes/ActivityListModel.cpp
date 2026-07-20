#include "../headers/ActivityListModel.h"

ActivityListModel::ActivityListModel(std::vector<Activity*>* source, QObject* parent) : QAbstractListModel(parent), dataSource(source) {}

int ActivityListModel::rowCount(const QModelIndex& parent) const {

    if (parent.isValid()) return 0;  
    return static_cast<int>(dataSource->size());
}

QVariant ActivityListModel::data(const QModelIndex& index, int role) const {

    if (!index.isValid()) return QVariant();

    int row = index.row();
    if (row < 0 || row >= static_cast<int>(dataSource->size())) return QVariant();

    Activity* activity = dataSource->at(row);
    switch (role) {

        case Qt::DisplayRole: return activity->getTitle();
        case Qt::ToolTipRole: return activity->getInfo();   // Polimorfico
        case ActivityPointerRole: return QVariant::fromValue(activity);

        default:
            return QVariant();
    }
}

Qt::ItemFlags ActivityListModel::flags(const QModelIndex& index) const {

    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void ActivityListModel::addActivity(Activity* activity) {

    if (!activity) return;

    int row = static_cast<int>(dataSource->size());

    beginInsertRows(QModelIndex(), row, row);
    dataSource->push_back(activity);
    endInsertRows();
}

void ActivityListModel::removeActivity(int row) {

    if (row < 0 || row >= static_cast<int>(dataSource->size())) return;

    beginRemoveRows(QModelIndex(), row, row);
    dataSource->erase(dataSource->begin() + row);
    endRemoveRows();
}

void ActivityListModel::refresh() {

    beginResetModel();
    // Nessuna modifica ai dati: Si richiede semplicemente tutto da capo.
    endResetModel();
}