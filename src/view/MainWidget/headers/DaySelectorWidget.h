#ifndef DAY_SELECTOR_WIDGET_H
#define DAY_SELECTOR_WIDGET_H

#include <QDate>
#include <QWidget>
#include <vector>
#include <QPushButton>
#include <QLabel>

////////////////
// DaySelectorWidget
////////////////

class DaySelectorWidget : public QWidget {
    Q_OBJECT

private:

    QDate current;
    std::vector<QLabel*> days;
    QPushButton* prevBtn;
    QPushButton* nextBtn;

    void updateDayLabels();

public:

    DaySelectorWidget(QWidget* parent = nullptr);

    QDate currentDate() const;
    void goToDate(const QDate& date);

public slots:

    void refreshSelector(int step);

signals:

    void dateChanged(QDate newDate);
};

#endif