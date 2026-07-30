#include "ActivityManager.h"
#include "MainWindow.h"
#include "AppController.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);
    QLocale::setDefault(QLocale(QLocale::Italian, QLocale::Italy));
    
    ActivityManager manager;
    // TEST TEMPORANEO — verifica che la catena Model->Controller->View funzioni
    ActivityData testData;
    testData.type = Activity::ActivityCategory::SimpleTask;
    testData.title = "Prova end-to-end";
    testData.description = "Se vedi questa riga, la catena funziona";
    manager.create(testData);

    
    MainWindow window;                          
    AppController controller(&manager, &window);
    
    window.show();    
    return app.exec();
}