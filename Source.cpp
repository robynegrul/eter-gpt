#include <QApplication>
#include "menuinterface.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MenuInterface window;
    window.show();

    return app.exec();
}
