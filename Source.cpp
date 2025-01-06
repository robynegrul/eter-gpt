#include <QApplication>
#include <QStackedWidget>
#include "MenuInterface.h"
#include "SelectGameModeInterface.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Creare ferestre
    MenuInterface* menu = new MenuInterface();
    SelectGameModeInterface* selectGameMode = new SelectGameModeInterface();

    // Creare StackedWidget
    QStackedWidget stackedWidget;
    stackedWidget.addWidget(menu);              // Index 0
    stackedWidget.addWidget(selectGameMode);    // Index 1
    stackedWidget.showFullScreen();

    // Conectare semnale pentru schimbarea paginilor
    QObject::connect(menu, &MenuInterface::switchToGameMenu, [&]() {
        stackedWidget.setCurrentWidget(selectGameMode);
        });

    QObject::connect(selectGameMode, &SelectGameModeInterface::switchToMenu, [&]() {
        stackedWidget.setCurrentWidget(menu);
        });

    // Conectare pentru inchiderea aplicatiei la apasarea ESC din orice meniu
    QObject::connect(menu, &MenuInterface::exitApplication, &app, &QApplication::quit);
    QObject::connect(selectGameMode, &SelectGameModeInterface::exitApplication, &app, &QApplication::quit);

    return app.exec();
}
