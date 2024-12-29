//commit 4
#include "menuinterface.h"
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QPalette>
#include <QFontDatabase>
#include <QMessageBox>

MenuInterface::MenuInterface(QWidget* parent)
    : QWidget(parent), layout(new QVBoxLayout(this)) {
    this->setFixedSize(1400, 750);
    this->setWindowTitle("ETER");

    this->setAttribute(Qt::WA_OpaquePaintEvent, false);
    this->setAutoFillBackground(false);

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

    int fontId = QFontDatabase::addApplicationFont("resources/Cinzel.ttf");
    if (fontId == -1) {
        qWarning() << "Fontul nu a fost încărcat corect!";
    }

    setupMenu();
}
//sfarsit commit 4

//commit 5
void MenuInterface::setupMenu() {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QPushButton* startButton = new QPushButton("Start New Game", this);
    QPushButton* loadButton = new QPushButton("Load Game", this);
    QPushButton* exitButton = new QPushButton("Exit Game", this);

    layout->addWidget(startButton);
    layout->addWidget(loadButton);
    layout->addWidget(exitButton);

    startButton->setFixedSize(300, 70);
    loadButton->setFixedSize(300, 70);
    exitButton->setFixedSize(300, 70);

    QFont cinzelFont("Cinzel", 50);
    startButton->setFont(cinzelFont);
    loadButton->setFont(cinzelFont);
    exitButton->setFont(cinzelFont);

    //sfarsit commit 5

        //commit 6

    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(10);

    QString buttonStyle =
        "QPushButton {"
        "    background-color: transparent;"
        "    border: 2px solid white;"
        "    color: white;"
        "    font-size: 30px;"
        "    padding: 10px;"
        "    border-radius: 10px;"
        "} "
        "QPushButton:hover {"
        "    background-color: rgba(255, 255, 255, 0.1);"
        "} ";

    //sfarsit commit 6

    //commit 7
    startButton->setStyleSheet(buttonStyle);
    loadButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    QObject::connect(startButton, &QPushButton::clicked, this, &MenuInterface::switchToNewGameScreen);
    QObject::connect(loadButton, &QPushButton::clicked, this, [&]() {
        QMessageBox::information(this, "Load Game", "Jocul va fi încărcat!");
        });
    QObject::connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
}
//sfarsit commit 7

    // commit 8
void MenuInterface::switchToNewGameScreen() {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    layout->addSpacerItem(new QSpacerItem(0, 300, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QLabel* selectGamemodeLabel = new QLabel("Select a gamemode:", this);
    QFont labelFont("Cinzel", 30);
    selectGamemodeLabel->setFont(labelFont);
    selectGamemodeLabel->setAlignment(Qt::AlignCenter);
    selectGamemodeLabel->setStyleSheet("QLabel { color: white; }");
    layout->addWidget(selectGamemodeLabel);

        //sfarsit commit 8
    
        //commit 9
    QVBoxLayout* buttonLayout = new QVBoxLayout();

    QPushButton* trainingButton = new QPushButton("Training", this);
    QPushButton* mageDuelButton = new QPushButton("Mage-Duel", this);
    QPushButton* elementalBattleButton = new QPushButton("Elemental-Battle", this);
    QPushButton* tournamentButton = new QPushButton("Tournament", this);
    QPushButton* timeAttackButton = new QPushButton("Time Attack", this);
    QPushButton* backButton = new QPushButton("Back to Menu", this);

    QFont cinzelFont("Cinzel", 30);
    trainingButton->setFont(cinzelFont);
    mageDuelButton->setFont(cinzelFont);
    elementalBattleButton->setFont(cinzelFont);
    tournamentButton->setFont(cinzelFont);
    timeAttackButton->setFont(cinzelFont);
    backButton->setFont(cinzelFont);

    //sfarsit commit 9

        //commit 10
    trainingButton->setFixedSize(200, 50);
    mageDuelButton->setFixedSize(200, 50);
    elementalBattleButton->setFixedSize(200, 50);
    tournamentButton->setFixedSize(200, 50);
    timeAttackButton->setFixedSize(200, 50);
    backButton->setFixedSize(200, 50);

    

    QString buttonStyle =
        "QPushButton {"
        "    background-color: transparent;"
        "    border: 2px solid white;"
        "    color: white;"
        "    font-size: 20px;"
        "    padding: 5px;"
        "    border-radius: 10px;"
        "} "
        "QPushButton:hover {"
        "    background-color: rgba(255, 255, 255, 0.1);"
        "} ";

    //sfarsit commit 10

    //commit 11

    trainingButton->setStyleSheet(buttonStyle);
    mageDuelButton->setStyleSheet(buttonStyle);
    elementalBattleButton->setStyleSheet(buttonStyle);
    tournamentButton->setStyleSheet(buttonStyle);
    timeAttackButton->setStyleSheet(buttonStyle);
    backButton->setStyleSheet(buttonStyle);


    layout->addWidget(trainingButton);
    layout->addWidget(mageDuelButton);
    layout->addWidget(elementalBattleButton);
    layout->addWidget(tournamentButton);
    layout->addWidget(timeAttackButton);
    layout->addWidget(backButton);

    //sfarsit commit 11

    //commit 12 
    layout->setSpacing(10);

    QObject::connect(backButton, &QPushButton::clicked, this, &MenuInterface::resetMenu);
    layout->addSpacerItem(new QSpacerItem(0, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));
}


void MenuInterface::resetMenu() {
    setupMenu();
}

//sfarsit commit 12
