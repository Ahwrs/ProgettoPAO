#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QUuid>



class Activity{

private:

    const QUuid ID;
    QString title;
    QString description;

public:

    enum class ActivityCategory { SimpleTaskType, CompositeTaskType, EventType, AppointmentType };
    
    Activity(const QString& t, const QString& d);
    virtual ~Activity();

    virtual QString getInfo() const = 0;    
    virtual ActivityCategory getCategory() const = 0;

    QUuid getID() const;
    QString getTitle() const;
    QString getDescription() const;

    void setTitle(const QString& t);
    void setDescription(const QString& d);

};

#endif