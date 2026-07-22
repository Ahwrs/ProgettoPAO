#ifndef ACTIVITY_DATA_H
#define ACTIVITY_DATA_H

#include "Activity.h"
#include <QString>
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

#endif