#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "DayViewWidget.h"
#include "ActivityRow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QStackedWidget* stack;
    DayViewWidget* dayView;
    QWidget* formPage = nullptr;

public:

    MainWindow(QWidget* parent = nullptr);
    DayViewWidget* getDayView() const;

    void showForm(QWidget* form);
    void showDayView();
    
signals:
    void selectWorkingFile();
};

#endif