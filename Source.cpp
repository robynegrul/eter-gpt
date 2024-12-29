/*#include "Game.h"
#include <iostream>

int main() {
    Game game;
    std::cout << "Select Game Mode (1 for Training Mode, 2 for Mage Duel, 3 for Elemental Battle, 4 for SpeedMode): ";
    int choice;
    std::cin >> choice;
    game.SetGameMode(choice);
    game.StartGame();

    return 0;
}*/

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char* argv[])
{
    // Crează aplicația Qt
    QApplication app(argc, argv);

    // Crează o fereastră principală
    QWidget window;

    // Setează dimensiunile ferestrei (mai mari)
    window.resize(600, 400);
    window.setWindowTitle("Fereastra Qt cu Buton");

    // Crează un buton
    QPushButton* button = new QPushButton("Apasă-mă!", &window);
    button->setGeometry(250, 170, 100, 40);  // Plasează butonul în mijlocul ferestrei

    // Conectează butonul la o funcție care închide fereastra când este apăsat
    QObject::connect(button, &QPushButton::clicked, &app, &QApplication::quit);

    // Afișează fereastra
    window.show();

    // Rulează aplicația Qt
    return app.exec();
}


