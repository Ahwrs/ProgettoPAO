#ifndef ACTIVITY_UTILITIES_H
#define ACTIVITY_UTILITIES_H

#include "Activity.h"
#include <iostream>
#include <string>
#include <sstream>
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
    bool isCompleted = false;
};

inline QString safeURL(const QString& url){

    return url.startsWith("https://") || url.startsWith("http://") ? url : "https://" + url;
}

inline QString CatToString(Activity::ActivityCategory c) {

    switch (c) {
        case Activity::ActivityCategory::Event: return "Event";
        case Activity::ActivityCategory::SimpleTask: return "SimpleTask";
        case Activity::ActivityCategory::CompositeTask: return "CompositeTask";
        case Activity::ActivityCategory::Appointment: return "Appointment";
    }
    return QString();
}

inline Activity::ActivityCategory CatFromString(const QString& s) {

    if (s == "Event") return Activity::ActivityCategory::Event;
    if (s == "SimpleTask") return Activity::ActivityCategory::SimpleTask;
    if (s == "CompositeTask") return Activity::ActivityCategory::CompositeTask;
    if (s == "Appointment") return Activity::ActivityCategory::Appointment;

    throw std::invalid_argument("Categoria sconosciuta nel JSON");
}

inline ActivityData toActivityData(const QJsonObject& obj) {

    ActivityData data;
    data.type = CatFromString(obj["CategoryType"].toString());
    data.title = obj["Title"].toString();
    data.description = obj["Description"].toString();
    
    QDate d = QDate::fromString(obj["Date"].toString(), Qt::ISODate);
    data.date = d.isValid() ? d : QDate::currentDate();

    QTime st = QTime::fromString(obj["StartTime"].toString(), Qt::ISODate);
    data.start = st.isValid() ? st : QTime::currentTime();

    QTime ed = QTime::fromString(obj["EndTime"].toString(), Qt::ISODate);
    data.end = ed.isValid() ? ed : QTime::currentTime();

    data.link = obj["Link"].toString();
    data.isOnline = obj["Online"].toBool();
    data.isCompleted = obj["Completed"].toBool();

    return data;
}

inline QString categoryStyle(Activity::ActivityCategory c) {

    QString QMsgStyle = "{"
        "ActivityRow QMessage{"
        ""
    "}";

    switch (c) {
        case Activity::ActivityCategory::Event:
            return "ActivityRow {"
                "   border: 2px solid rgba(59,130,246,1);"
                "   border-radius: 6px;"
                "   padding: 5px 10px;"
                "   background-color: rgba(59,130,246,0.1);"
                "   color: white;"
                "}"
                "   ActivityRow QLabel, ActivityRow QWidget {"
                "   color: white;"
                "   font-family: Arial;"
                "   background-color: transparent;"
                "   font-weight: 700;"
                "}";                

        case Activity::ActivityCategory::Appointment:
            return "ActivityRow {"
                "   border: 2px solid rgba(124,58,237,1);" 
                "   border-radius: 6px;"
                "   padding: 5px 10px;"                
                "   background-color: rgba(124,58,237,0.1);" 
                "   color: white;"
                "}"
                "   ActivityRow QLabel, ActivityRow QWidget {"
                "   color: white;"
                "   font-family: Arial;"
                "   background-color: transparent;"
                "   font-weight: 700;"
                "}";

        case Activity::ActivityCategory::SimpleTask:
            return "ActivityRow {"
                "   border: 2px solid rgba(124,58,237,1);"
                "   border-radius: 6px;"
                "   padding: 5px 10px;"
                "   background-color: rgba(124,58,237, 0.1);"
                "}"
                "   ActivityRow QLabel, ActivityRow QWidget {"
                "   color: rgba(240, 229, 255, 0.9);"
                "   font-family: Arial;"
                "   background-color: transparent;"
                "   font-weight: 700;"
                "}"
                "ActivityRow:disabled {"
                "   background-color: rgba(66, 66, 66, 0.5);"
                "}"
                "ActivityRow:disabled QPushButton{"
                "   border: none;"
                "}";

        case Activity::ActivityCategory::CompositeTask:
            return "ActivityRow {"
                "   border: 2px solid rgba(245,158,11,1);" 
                "   border-radius: 6px;"
                "   padding: 5px 10px;"                
                "   background-color: rgba(245,158,11,0.1);" 
                "}"
                "   ActivityRow QLabel, ActivityRow QWidget {"
                "   color: #F59E0B;"
                "   font-family: Arial;"
                "   background-color: transparent;"
                "   font-weight: 700;"
                "}";
    }
    return QString();
}

#endif
