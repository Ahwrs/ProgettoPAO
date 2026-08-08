#include "ActivityManager.h"
#include "MainWindow.h"
#include "AppController.h"
#include <QApplication>

////////////////
// Funzione principale
////////////////

int main(int argc, char *argv[])
{
    // Imposta il locale italiano
    QApplication app(argc, argv);
    QLocale::setDefault(QLocale(QLocale::Italian, QLocale::Italy));

    // Inizializza Model, View e Controller
    ActivityManager manager;
    MainWindow window;
    AppController controller(&manager, &window);

    // Mostra la finestra principale e avvia il loop eventi
    window.show();
    return app.exec();
}