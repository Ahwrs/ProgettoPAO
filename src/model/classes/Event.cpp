#include "../headers/Event.h"
#include <exception>

Event::Event(const QString& title, const QString& description,
          const QDate& date, const QTime& start, const QTime& end) :

          Activity(title, description),
          date(date), startTime(start), endTime(endTime) {}

QString Event::getInfo() const {

    return getDescription() + "\nData: " + date.toString("dd/MM/yyyy") +
           "\nOra: " + startTime.toString("HH:mm") + " - " + endTime.toString("HH:mm");
}
