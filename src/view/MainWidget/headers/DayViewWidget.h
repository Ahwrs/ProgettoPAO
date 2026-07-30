#ifndef DAY_VIEW_WIDGET_H
#define DAY_VIEW_WIDGET_H

#include "ActivityRow.h"
#include "DaySelectorWidget.h"
#include <QWidget>
#include <QBoxLayout>

class DayViewWidget : public QWidget {
    Q_OBJECT

private:

    DaySelectorWidget* selector;
    QVBoxLayout* TLayout;     
    QVBoxLayout* ELayout;
    QPushButton* Add;
    void repositionAddButton();

    void replaceLayoutContents(QBoxLayout* layout, const std::vector<ActivityRow*>& rows);

protected:
    void resizeEvent(QResizeEvent* event) override;

public:

    DayViewWidget(QWidget* parent = nullptr);

    void setTaskRows(const std::vector<ActivityRow*>& rows);
    void setEventRows(const std::vector<ActivityRow*>& rows);

signals:

    void newActivityRequested();
};

#endif