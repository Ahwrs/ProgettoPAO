#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QPushButton button("Hello Qt!");
    button.resize(300, 200);
    button.show();

    return app.exec();
}