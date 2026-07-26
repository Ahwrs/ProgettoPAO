#include "MainWindow.h"
#include "DaySelectorWidget.h"

#include <QBoxLayout>
#include <QLabel>

MainWindow::MainWindow(ActivityManager* m) : manager(m) {

    setMinimumSize(600, 500);
    setStyleSheet("background-color: #070b0f; color: white;");

    stack = new QStackedWidget();

    DaySelectorWidget* selector = new DaySelectorWidget();
    QLabel* formPlaceholder = new QLabel("Form (da costruire)");

    stack->addWidget(selector);
    stack->addWidget(formPlaceholder);

    setCentralWidget(stack);
}