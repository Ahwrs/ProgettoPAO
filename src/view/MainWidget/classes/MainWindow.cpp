#include "MainWindow.h"
#include "DayViewWidget.h"
#include <QMenuBar>
#include <QAction>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

    setMinimumSize(500, 600);
    setStyleSheet("background-color: #070b0f; color: white;");

    // --- Menu ---
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* selectFileAction = fileMenu->addAction("Seleziona file di lavoro...");
    connect(selectFileAction, &QAction::triggered, this, [this]{
        emit selectWorkingFile();
    });

    // --- Stack ---
    stack = new QStackedWidget();
    dayView = new DayViewWidget();
    stack->addWidget(dayView);
    stack->setCurrentIndex(0);

    setCentralWidget(stack);
}

DayViewWidget* MainWindow::getDayView() const {
    return dayView;
}

void MainWindow::showForm(QWidget* form) {

    formPage = form;
    stack->addWidget(formPage);
    stack->setCurrentWidget(formPage);
}

void MainWindow::showDayView() {

    stack->setCurrentWidget(dayView);
    if (formPage) {
        
        stack->removeWidget(formPage);
        formPage->deleteLater();
        formPage = nullptr;
    }
}