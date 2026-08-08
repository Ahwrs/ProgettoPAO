#ifndef ACTIVITY_UTILITIES_H
#define ACTIVITY_UTILITIES_H

#include "Activity.h"
#include <QString>
#include <QDate>
#include <QTime>
#include <vector>

////////////////
// Strutture dati
////////////////

struct SubTaskData {
    QUuid id;
    QString title;
    QString description;
};

struct ActivityData {
    Activity::ActivityCategory type;

    QString title;
    QString description;

    QDate date;
    QTime start;
    QTime end;
    QString link;

    bool isOnline = false;
    bool isCompleted = false;

    std::vector<SubTaskData> subTasks;  // Usato solo se type == CompositeTask
};

////////////////
// Utility URL
////////////////

inline QString safeURL(const QString& url) {
    return (url.startsWith("https://") || url.startsWith("http://")) ? url : "https://" + url;
}

////////////////
// Conversione categorie (stringa <-> enum)
////////////////

inline QString CatToString(Activity::ActivityCategory c) {

    switch (c) {
        case Activity::ActivityCategory::Event:         return "Evento";
        case Activity::ActivityCategory::SimpleTask:    return "Task Semplice";
        case Activity::ActivityCategory::CompositeTask: return "Task Composta";
        case Activity::ActivityCategory::Appointment:   return "Appuntamento";
    }
    return QString();
}

inline Activity::ActivityCategory CatFromString(const QString& s) {

    if (s == "Evento")         return Activity::ActivityCategory::Event;
    if (s == "Task Semplice")    return Activity::ActivityCategory::SimpleTask;
    if (s == "Task Composta") return Activity::ActivityCategory::CompositeTask;
    if (s == "Appuntamento")   return Activity::ActivityCategory::Appointment;

    throw std::invalid_argument("Categoria sconosciuta nel JSON");
}

////////////////
// Conversione da JSON a ActivityData
////////////////

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

////////////////
// Stile UI per categoria
////////////////

inline QString categoryStyle(Activity::ActivityCategory c) {
    switch (c) {
        case Activity::ActivityCategory::Event:
            return "#Root {"
                "   border: 1px solid rgba(34,197,94,60);"
                "   border-left: 4px solid rgba(34,197,94,255);"
                "   border-radius: 8px;"
                "   padding: 8px;"
                "   background-color: rgba(34,197,94,15);"
                "}"
                "ActivityRow QLabel, ActivityRow QWidget {"
                "   color: rgb(220, 252, 231);"
                "   font-family: Arial;"
                "   background-color: transparent;"
                "   font-weight: 700;"
                "}"
                "#cardIcon {"
                "   border: 2px solid rgba(34,197,94,255);"
                "   border-radius: 12px;"
                "   background-color: transparent;"
                "}"
                "#categoryBadge {"
                "   background-color: rgba(34,197,94,40);"
                "   color: rgba(34,197,94,255);"
                "   border-radius: 8px;"
                "   padding: 2px 8px;"
                "   font-size: 8pt;"
                "   font-weight: 600;"
                "}";

        case Activity::ActivityCategory::Appointment:
            return "#Root {"
                "   border: 1px solid rgba(34,211,238,60);"
                "   border-left: 4px solid rgba(34,211,238,255);"
                "   border-radius: 8px;"
                "   padding: 8px;"
                "   background-color: rgba(34,211,238,15);"
                "}"
                "ActivityRow QLabel, ActivityRow QWidget {"
                "   color: rgb(207, 250, 254);"
                "   font-family: Arial;"
                "   background-color: transparent;"
                "   font-weight: 700;"
                "}"
                "#cardIcon {"
                "   border: 2px solid rgba(34,211,238,255);"
                "   border-radius: 12px;"
                "   background-color: transparent;"
                "}"
                "#categoryBadge {"
                "   background-color: rgba(34,211,238,40);"
                "   color: rgba(34,211,238,255);"
                "   border-radius: 8px;"
                "   padding: 2px 8px;"
                "   font-size: 8pt;"
                "   font-weight: 600;"
                "}";

        case Activity::ActivityCategory::SimpleTask:
            return "#Root {"
                "   border: 1px solid rgba(124,58,237,60);"
                "   border-left: 4px solid rgba(124,58,237,255);"
                "   border-radius: 8px;"
                "   padding: 8px;"
                "   background-color: rgba(124,58,237,15);"
                "}"
                "ActivityRow QLabel, ActivityRow QWidget {"
                "   color: rgba(240, 229, 255, 230);"
                "   font-family: Arial;"
                "   background-color: transparent;"
                "   font-weight: 700;"
                "}"
                "#cardIcon {"
                "   border: 2px solid rgba(124,58,237,255);"
                "   border-radius: 12px;"
                "   background-color: transparent;"
                "}"
                "#categoryBadge {"
                "   background-color: rgba(124,58,237,40);"
                "   color: rgba(124,58,237,255);"
                "   border-radius: 8px;"
                "   padding: 2px 8px;"
                "   font-size: 8pt;"
                "   font-weight: 600;"
                "}"
                "#Root:disabled {"
                "   background-color: rgba(66, 66, 66, 128);"
                "}"
                "#Root:disabled QPushButton{"
                "   border: none;"
                "}";

        case Activity::ActivityCategory::CompositeTask:
            return "#Root {"
                "   border: 1px solid rgba(245,158,11,60);"
                "   border-left: 4px solid rgba(245,158,11,255);"
                "   border-radius: 8px;"
                "   padding: 8px;"
                "   background-color: rgba(245,158,11,15);"
                "}"
                "ActivityRow QLabel, ActivityRow QWidget {"
                "   color: white;"
                "   font-family: Arial;"
                "   background-color: transparent;"
                "   font-weight: 700;"
                "}"
                "#cardIcon {"
                "   border: 2px solid rgba(245,158,11,255);"
                "   border-radius: 12px;"
                "   background-color: transparent;"
                "}"
                "#categoryBadge {"
                "   background-color: rgba(245,158,11,40);"
                "   color: rgba(245,158,11,255);"
                "   border-radius: 8px;"
                "   padding: 2px 8px;"
                "   font-size: 8pt;"
                "   font-weight: 600;"
                "}";
    }
    return QString();
}

#endif