#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>

class Activity{

private:

    const int ID;
    QString title;
    QString description;

public:

    Activity(const QString& t, const QString& d);
    virtual ~Activity();

    virtual QString getInfo() const = 0;

    QString getTitle() const;
    QString getDescription() const;
    
};

#endif 
