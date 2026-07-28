#include "ActivityManager.h"
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);
    QLocale::setDefault(QLocale(QLocale::Italian, QLocale::Italy));
    
    ActivityManager manager;         // vive per tutta la durata del programma
    MainWindow window(&manager);     // iniettato, MainWindow non lo possiede

    window.show();
    return app.exec();
}