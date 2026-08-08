#ifndef DAY_VIEW_WIDGET_H
#define DAY_VIEW_WIDGET_H

#include "SearchWidget.h"
#include "TimelineWidget.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <vector>

// Forwarding declarations
class DaySelectorWidget;
class ActivityRow;

////////////////
// DayViewWidget
////////////////

class DayViewWidget : public QWidget {
    Q_OBJECT

private:

    // Metodi per setup
    void setupUI();
    void setupConnections();
    void repositionAddButton();

    // Widget membri
    DaySelectorWidget* selector;
    QPushButton* datePickerBtn;
    SearchWidget* searchBar;

    QScrollArea* scrollArea;
    TimelineWidget* timeline;

    QWidget* taskContainer;
    QVBoxLayout* taskLayout;

    QWidget* eventSection;

    QWidget* searchContainer;
    QVBoxLayout* searchLayout;

    QPushButton* addBtn;

protected:

    void resizeEvent(QResizeEvent* event) override;

public:
    
    DayViewWidget(QWidget* parent = nullptr);

    void setTaskRows(const std::vector<ActivityRow*>& rows);
    void setEventRows(const std::vector<ActivityRow*>& rows);
    void setSearchResults(const std::vector<ActivityRow*>& rows);

    QDate currentDate() const;
    void goToToday();
    void focusSearch();
    void clearSearch();

signals:
    void newActivityRequested();
    void dayChanged(QDate newDate);
    void searchCriteriaChanged(const SearchCriteria& criteria);
    void searchCleared();
};

#endif