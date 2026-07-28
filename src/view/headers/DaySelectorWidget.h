#ifndef DAY_SELECTOR_WIDGET_H
#define DAY_SELECTOR_WIDGET_H

#include <QDate>
#include <QWidget>
#include <vector>
#include <QPushButton>
#include <QLabel>

class DaySelectorWidget : public QWidget {
    Q_OBJECT

private:

    QDate current;
    std::vector<QLabel*> days;
    QPushButton* next;
    QPushButton* last;

public:

    DaySelectorWidget(QWidget* parent = nullptr);
    void refreshSelector(int day);

};

#endif