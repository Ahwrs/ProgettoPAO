#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QUuid>

struct ActivityData; // Forward Declaration

class Activity{

private:

    const QUuid ID;
    QString title;
    QString description;

public:

    enum class ActivityCategory{Event, SimpleTask, CompositeTask, Appointment};
    
    Activity(const QString& t, const QString& d);
    virtual ~Activity();

    virtual QString getInfo() const = 0; 
    virtual ActivityCategory getCategory() const = 0;

    virtual void update(const ActivityData& newData);

    QUuid getID() const;
    QString getTitle() const;
    QString getDescription() const;

    void setTitle(const QString& t);
    void setDescription(const QString& d);

};

#endif