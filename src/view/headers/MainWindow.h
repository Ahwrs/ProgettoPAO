#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "ActivityManager.h"

class DayViewWidget;

class MainWindow : public QMainWindow {

    ActivityManager* manager;
    QStackedWidget* stack;      
    DayViewWidget* dayView;

public:

    MainWindow(ActivityManager* m);
};

#endif