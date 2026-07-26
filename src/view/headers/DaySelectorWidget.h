#ifndef DAY_SELECTOR_WIDGET_H
#define DAY_SELECTOR_WIDGET_H

#include <QDate>
#include <vector>
#include <QPushButton>
#include <QLabel>

class DaySelectorWidget : public QWidget {

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