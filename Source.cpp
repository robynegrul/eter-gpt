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
#include <QPixmap>
#include <QPalette>
#include <QLabel>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Crează o fereastră principală
    QWidget window;

    // Setează dimensiunile ferestrei (1300x700)
    window.resize(1300, 700);
    window.setWindowTitle("Fereastra Qt cu Buton și Fundal");

    // Încarcă imaginea
    QPixmap background("resources/MainScreen.png");

    // Verifică dacă imaginea a fost încărcată corect
    if (background.isNull()) {
        qWarning("Imaginea nu a putut fi încărcată.");
    }
    else {
        // Redimensionează imaginea pentru a se potrivi perfect ferestrei
        QPixmap scaledBackground = background.scaled(window.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        // Setează imaginea redimensionată ca fundal
        QPalette palette;
        palette.setBrush(QPalette::Window, scaledBackground);  // Schimbă Background cu Window
        window.setPalette(palette);
    }

    // Crează un buton
    QPushButton* button = new QPushButton("Apasă-mă!", &window);
    button->setGeometry(550, 300, 200, 50);  // Plasează butonul în mijlocul ferestrei

    // Conectează butonul la o funcție care închide fereastra când este apăsat
    QObject::connect(button, &QPushButton::clicked, &app, &QApplication::quit);

    // Afișează fereastra
    window.show();

    // Rulează aplicația Qt
    return app.exec();
}
