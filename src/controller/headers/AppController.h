#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <QObject>
#include "ActivityManager.h"
#include "MainWindow.h"

////////////////
// Controller principale
////////////////
class AppController : public QObject {
    Q_OBJECT

private:
    ActivityManager* manager;
    MainWindow* window;
    QString workFile;

    QDate curDay;
    SearchCriteria lastSearch;
    bool searchActive = false;

    //////////////////
    // Metodi interni
    //////////////////
    void refreshList();
    void openForm(Activity* toEdit);
    ActivityRow* buildRow(Activity* act);
    void saveFile();
    void saveAsFile();

public:
    AppController(ActivityManager* m, MainWindow* w, QObject* parent = nullptr);

public slots:

    //////////////////
    // Slot pubblici
    //////////////////
    void viewDetails(const QUuid& id);
    void newActivity();
    void editActivity(const QUuid& id);
    void onSearchChanged(const SearchCriteria& c);
    void openFile();
    void saveRequested();
    void saveShortcut();
    void saveAsShortcut();
};

#endif