#include "SelectGameModeInterface.h"
#include <QDebug>
#include <QPalette>
#include <QPixmap>
#include <QFontDatabase>

SelectGameModeInterface::SelectGameModeInterface(QWidget* parent) : QWidget(parent) {
    setupUi();
}

SelectGameModeInterface::~SelectGameModeInterface() {
}

void SelectGameModeInterface::setupUi() {
    int regularFontId = QFontDatabase::addApplicationFont("C:/Users/paulj/eter-gpt/resources/Cinzel.ttf");
    if (regularFontId == -1) {
        qDebug() << "Failed to load regular font!";
    }
    QString regularFontFamily = QFontDatabase::applicationFontFamilies(regularFontId).isEmpty()
        ? QString()
        : QFontDatabase::applicationFontFamilies(regularFontId).at(0);

    QFont regularFont(regularFontFamily);

 
    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 100, 0, 0);
    outerLayout->setSpacing(0);


    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setContentsMargins(0, 300, 0, 0);
    mainLayout->setSpacing(10);

    Training = new QPushButton("TRAINING", this);
    Training->setStyleSheet("font-size: 20px; color: white; border: 2.5px solid white; padding: 9px 78px; border-radius: 5px;");
    Training->setFont(regularFont);
    Training->setMinimumWidth(200);
    mainLayout->addWidget(Training);

    MageDuel = new QPushButton("MAGE-DUEL", this);
    MageDuel->setStyleSheet("font-size: 20px; color: white; border: 2.5px solid white; padding: 9px 78px; border-radius: 5px;");
    MageDuel->setFont(regularFont);
    MageDuel->setMinimumWidth(200);
    mainLayout->addWidget(MageDuel);

    ElementalBattle = new QPushButton("ELEMENTAL-BATTLE", this);
    ElementalBattle->setStyleSheet("font-size: 20px; color: white; border: 2.5px solid white; padding: 9px 78px; border-radius: 5px;");
    ElementalBattle->setFont(regularFont);
    ElementalBattle->setMinimumWidth(200);
    mainLayout->addWidget(ElementalBattle);

    Tournament = new QPushButton("TOURNAMENT", this);
    Tournament->setStyleSheet("font-size: 20px; color: white; border: 2.5px solid white; padding: 9px 78px; border-radius: 5px;");
    Tournament->setFont(regularFont);
    Tournament->setMinimumWidth(200);
    mainLayout->addWidget(Tournament);

    TimeAttack = new QPushButton("TIME ATTACK", this);
    TimeAttack->setStyleSheet("font-size: 20px; color: white; border: 2.5px solid white; padding: 9px 78px; border-radius: 5px;");
    TimeAttack->setFont(regularFont);
    TimeAttack->setMinimumWidth(200);
    mainLayout->addWidget(TimeAttack);

  
    outerLayout->addLayout(mainLayout);

    QHBoxLayout* backButtonLayout = new QHBoxLayout();
    backButtonLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    backButtonLayout->setContentsMargins(10, 10, 10, 10);

    BackButton = new QPushButton("🠔", this); 
    BackButton->setStyleSheet("font-size: 30px; color: white; border: 2.0px solid white; padding: 4px 16px; border-radius: 5px;");
    BackButton->setFont(regularFont);
    BackButton->setMinimumWidth(50);
    backButtonLayout->addWidget(BackButton);

  
    outerLayout->addLayout(backButtonLayout);

    setLayout(outerLayout);

    connect(BackButton, &QPushButton::clicked, this, &SelectGameModeInterface::switchToMenu);

    setScaledBackground();
}


void SelectGameModeInterface::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        emit exitApplication(); 
    }
    else {
        QWidget::keyPressEvent(event);
    }
}



void SelectGameModeInterface::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    setScaledBackground();
}


void SelectGameModeInterface::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    setScaledBackground(); 
}

void SelectGameModeInterface::setScaledBackground() {
    QPixmap background("C:/Users/paulj/eter-gpt/resources/MainScreen.png");
    if (!background.isNull()) {
        background = background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, background);
        this->setPalette(palette);
    }
    else {
        qDebug() << "Failed to load background image!";
    }
    this->setAutoFillBackground(true);

}
