#ifndef TIMELINE_WIDGET_H
#define TIMELINE_WIDGET_H

#include <QWidget>
#include <vector>

// Forwarding declarations
class ActivityRow;
class EventRow;

////////////////
// TimelineWidget
////////////////

class TimelineWidget : public QWidget {
    Q_OBJECT

private:
    std::vector<EventRow*> eventRows;

public:

    TimelineWidget(QWidget* parent = nullptr);
    void setEventRows(const std::vector<ActivityRow*>& rows);

protected:

    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private slots:

    void repositionEvents();
};

#endif