#include "ActivityManager.h"
#include "MainWindow.h"
#include "AppController.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);
    QLocale::setDefault(QLocale(QLocale::Italian, QLocale::Italy));
    
    ActivityManager manager;
    MainWindow window;                          
    AppController controller(&manager, &window);
    
    window.show();    
    return app.exec();
}