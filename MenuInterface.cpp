#include "menuinterface.h"
#include <QPushButton>
#include <QPixmap>
#include <QPalette>
#include <QFontDatabase>
#include <QMessageBox>

MenuInterface::MenuInterface(QWidget* parent) : QWidget(parent) {
    // Setează dimensiunile ferestrei
    this->setFixedSize(1400, 750);
    this->setWindowTitle("Meniu Joc");

    // Permite transparența ferestrei
    this->setAttribute(Qt::WA_OpaquePaintEvent, false);
    this->setAutoFillBackground(false);

    // Încarcă imaginea de fundal
    QPixmap background("resources/MainScreen.png");
    if (background.isNull()) {
        qWarning("Imaginea nu a putut fi încărcată.");
    }
    else {
        QPixmap scaledBackground = background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, scaledBackground);
        this->setPalette(palette);
    }

    // Încarcă fontul
    int fontId = QFontDatabase::addApplicationFont("resources/Cinzel.ttf");
    if (fontId == -1) {
        qWarning() << "Fontul nu a fost încărcat corect!";
    }

    // Creează layout-ul și butoanele
    setupMenu();
}

void MenuInterface::setupMenu() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Creează butoanele
    QPushButton* startButton = new QPushButton("Start New Game", this);
    QPushButton* loadButton = new QPushButton("Load Game", this);

    // Adaugă butoanele în layout
    layout->addWidget(startButton);
    layout->addWidget(loadButton);

    // Setează dimensiunile și fontul butoanelor
    startButton->setFixedSize(300, 70);  // Dimensiuni mai mari pentru butoane
    loadButton->setFixedSize(300, 70);   // Dimensiuni mai mari pentru butoane

    QFont cinzelFont("Cinzel", 50, QFont::Bold);  // Font mai mare
    startButton->setFont(cinzelFont);
    loadButton->setFont(cinzelFont);

    // Aliniază butoanele în centru
    layout->setAlignment(Qt::AlignCenter);

    // Adaugă mai mult spațiu între butoane
    layout->setSpacing(30);  // Spațiu între butoane

    // Setează stilul butoanelor: fundal transparent și margine albă
    startButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: 2px solid white;"  // Marginea albă
        "    color: white;"  // Culoarea textului
        "    font-size: 30px;"  // Dimensiune font mai mare
        "    padding: 10px;"
        "    border-radius: 10px;"  // Colțuri rotunjite
        "} "
        "QPushButton:hover {"
        "    background-color: rgba(255, 255, 255, 0.1);"  // Efect de hover
        "} "
    );

    loadButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: 2px solid white;"  // Marginea albă
        "    color: white;"  // Culoarea textului
        "    font-size: 30px;"  // Dimensiune font mai mare
        "    padding: 10px;"
        "    border-radius: 10px;"  // Colțuri rotunjite
        "} "
        "QPushButton:hover {"
        "    background-color: rgba(255, 255, 255, 0.1);"  // Efect de hover
        "} "
    );

    // Conectează butoanele la acțiuni
    QObject::connect(startButton, &QPushButton::clicked, this, [&]() {
        QMessageBox::information(this, "Start Game", "Jocul va începe!");
        });

    QObject::connect(loadButton, &QPushButton::clicked, this, [&]() {
        QMessageBox::information(this, "Load Game", "Jocul va fi încărcat!");
        });
}
