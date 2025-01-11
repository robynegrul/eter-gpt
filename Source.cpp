//#include <QApplication>
//#include <QStackedWidget>
//#include "MenuInterface.h"
//#include "SelectGameModeInterface.h"
//#include "TrainingInterface.h"
//
//int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//
//    MenuInterface* menu = new MenuInterface();
//    SelectGameModeInterface* selectGameMode = new SelectGameModeInterface();
//    TrainingInterface* trainingInterface = new TrainingInterface();
//
//    QStackedWidget stackedWidget;
//    stackedWidget.addWidget(menu);
//    stackedWidget.addWidget(selectGameMode);
//    stackedWidget.addWidget(trainingInterface);
//    stackedWidget.showFullScreen();
//
//    // Conectări existente
//    QObject::connect(menu, &MenuInterface::switchToGameMenu, [&]() {
//        stackedWidget.setCurrentWidget(selectGameMode);
//        });
//
//    QObject::connect(selectGameMode, &SelectGameModeInterface::switchToMenu, [&]() {
//        stackedWidget.setCurrentWidget(menu);
//        });
//
//    QObject::connect(selectGameMode, &SelectGameModeInterface::switchToTraining, [&]() {
//        stackedWidget.setCurrentWidget(trainingInterface);
//        trainingInterface->startGame();  // Add this if you want to auto-start the game
//        });
//
//    // Exit connections
//    QObject::connect(menu, &MenuInterface::exitApplication, &app, &QApplication::quit);
//    QObject::connect(selectGameMode, &SelectGameModeInterface::exitApplication, &app, &QApplication::quit);
//    QObject::connect(trainingInterface, &TrainingInterface::exitApplication, &app, &QApplication::quit);
//
//    return app.exec();
//}

#include "Game.h"
#include <iostream>

int main() {
    Game game;
    std::cout << "Select Game Mode (1 for Training Mode, 2 for Mage Duel, 3 for Elemental Battle, 4 for SpeedMode): ";
    int choice;
    std::cin >> choice;
    game.SetGameMode(choice);
    game.StartGame();

    return 0;
}