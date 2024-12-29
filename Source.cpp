#include <QApplication>
#include "menuinterface.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Creează instanța clasei MenuInterface
    MenuInterface window;

    // Afișează fereastra principală
    window.show();

    return app.exec();
}
