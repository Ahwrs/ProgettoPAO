#ifndef SEARCH_WIDGET_H
#define SEARCH_WIDGET_H

#include "ActivityUtilities.h"
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QCheckBox>

struct SearchCriteria {
    QString title;

    bool hasCategory = false;
    Activity::ActivityCategory category;

    bool hasStartDate = false;
    QDate startDate;

    bool hasEndDate = false;
    QDate endDate;
};

////////////////
// SearchWidget
////////////////

class SearchWidget : public QWidget {
    Q_OBJECT

private:

    // Metodi privati
    void setupUI();
    void setupConnections();
    void clearAllExcept(QWidget* except);
    SearchCriteria collectCriteria() const;

    // Widget membri
    QLineEdit* titleField;
    QComboBox* categoryCombo;
    QDateEdit* startDateField;
    QDateEdit* endDateField;
    QCheckBox* exclusiveCheckbox;
    QWidget* content;

    static const QDate SENTINEL;

public:

    SearchWidget(QWidget* parent = nullptr);
    void openPanel();

signals:

    void criteriaChanged(const SearchCriteria& criteria);
};

#endif