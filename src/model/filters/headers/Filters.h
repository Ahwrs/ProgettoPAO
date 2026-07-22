#ifndef FILTERS_H
#define FILTERS_H

#include "ActivityFilter.h"
#include "Event.h"
#include "Task.h"
#include <QString>
#include <QDate>
#include <vector>

// ---------------------------------------------------------
// TitleFilter — Case-insensitive nel titolo
// ---------------------------------------------------------
class TitleFilter : public ActivityFilter {
private:
    QString subString;

public:
    
    TitleFilter(const QString& text) : subString(text.trimmed()) {}

    bool matches(const Activity* activity) const override {

        if (subString.isEmpty()) return true;   
        return activity->getTitle().contains(subString, Qt::CaseInsensitive);
    }
};

// ---------------------------------------------------------
// DateRangeFilter — valido solo per Event/Appointment
// ---------------------------------------------------------
class DateRangeFilter : public ActivityFilter {
private:
    QDate start;
    QDate end;

public:
    
    DateRangeFilter(const QDate& start, const QDate& end) : start(start), end(end) {}

    bool matches(const Activity* activity) const override {

        const Event* event = dynamic_cast<const Event*>(activity);
        if (!event) return false;   // SimpleTask/CompositeTask non hanno data: Esclusi

        QDate d = event->getDate();
        return d >= start && d <= end;
    }
};

// ---------------------------------------------------------
// CategoryFilter — Filtra per tipo concreto
// ---------------------------------------------------------
class CategoryFilter : public ActivityFilter {
private:

    Activity::ActivityCategory category;
public:
    
    CategoryFilter(Activity::ActivityCategory category) : category(category) {}

    bool matches(const Activity* activity) const override {
        return activity->getCategory() == category;
    }
};

// ---------------------------------------------------------
// CompletionFilter — valido solo per i Task
// ---------------------------------------------------------
class CompletionFilter : public ActivityFilter {
private:
    
    bool completedTask;
public:
    
    CompletionFilter(bool completed) : completedTask(completed) {}
    bool matches(const Activity* activity) const override {

        const Task* task = dynamic_cast<const Task*>(activity);

        if (!task) return false;   // Event/Appointment non hanno stato di completamento: esclusi

        return task->isCompleted() == completedTask;
    }
};

// ---------------------------------------------------------
// CompositeFilter — combina più filtri in AND oppure OR
// ---------------------------------------------------------
class CompositeFilter : public ActivityFilter {
public:
    
    enum class LogicMode { And, Or };

private:

    std::vector<std::unique_ptr<ActivityFilter>> filters;
    LogicMode mode;

public:
    
    CompositeFilter(LogicMode mode) : mode(mode) {}
    CompositeFilter(const CompositeFilter& cs) = delete;
    ~CompositeFilter() override = default;

    CompositeFilter& operator=(const CompositeFilter&) = delete;

    void addFilter(std::unique_ptr<ActivityFilter> filter) { // Ricordarsi di usare std::make_unique<> quando si invoca addFilter su un puntatore non unique.
        if (filter)
            filters.push_back(std::move(filter));
    }

    bool matches(const Activity* activity) const override {

        if (filters.empty()) return true;   // nessun filtro attivo: tutto passa
        if (mode == LogicMode::And) {

            for (const auto& f : filters) {
                if (!f->matches(activity))
                    return false;
            }
            return true;

        } else { // LogicMode::Or

            for (const auto& f : filters) {
                if (f->matches(activity))
                    return true;
            }
            return false;
        }
    }
};

#endif