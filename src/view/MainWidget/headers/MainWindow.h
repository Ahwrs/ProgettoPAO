#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QAction>
#include "DayViewWidget.h"
#include "ActivityRow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:

    QStackedWidget* stack;
    DayViewWidget* dayView;
    QWidget* formPage = nullptr;
    QLabel* workingFile;

    QAction* openAction;
    void setupShortcuts();

public:

    MainWindow(QWidget* parent = nullptr);
    DayViewWidget* getDayView() const;

    void showForm(QWidget* form);
    void showDayView();
    void setCurrentFile(const QString& file);
    
protected:

    void closeEvent(QCloseEvent* event) override;

signals:
    void openWorkingFileRequested();
    void saveRequested();
    void closing();

    void newActivityShortcut();
    void saveShortcut();
    void saveAsShortcut();
};

#endif