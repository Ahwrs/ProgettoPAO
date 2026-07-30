#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <QObject>
#include "ActivityManager.h"
#include "MainWindow.h"

class AppController : public QObject {
    Q_OBJECT

private:

    ActivityManager* manager;
    MainWindow* mainWindow;

    void refreshActivityList();
    void openForm(Activity* toEdit);   // nullptr = creazione

public:

    AppController(ActivityManager* m, MainWindow* w, QObject* parent = nullptr);
    
public slots:

    void onNewActivityRequested();
    void onEditRequested(const QUuid& id);
};

#endif