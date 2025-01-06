#include "MenuInterface.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPalette>
#include <QPixmap>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QDebug>
#include <QFontDatabase>
#include <QApplication>

MenuInterface::MenuInterface(QWidget* parent) : QWidget(parent) {
    setupUi();
}

MenuInterface::~MenuInterface() {
}

void MenuInterface::setupUi() {
    int regularFontId = QFontDatabase::addApplicationFont("resources/Cinzel.ttf");
    if (regularFontId == -1) {
        qDebug() << "Failed to load regular font!";
    }
    QString regularFontFamily = QFontDatabase::applicationFontFamilies(regularFontId).isEmpty()
        ? QString()
        : QFontDatabase::applicationFontFamilies(regularFontId).at(0);

    QFont regularFont(regularFontFamily);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setContentsMargins(0, 100, 0, 0);
    mainLayout->setSpacing(10);

    startButton = new QPushButton("START NEW GAME", this);
    startButton->setStyleSheet(R"(
        QPushButton {
            font-size: 20px;
            color: white;
            border: 2.5px solid white;
            padding: 9px 78px;
            border-radius: 5px;
            background-color: transparent;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 50);
        }
    )");
    startButton->setFont(regularFont);
    startButton->setMinimumWidth(200);
    mainLayout->addWidget(startButton);

    loadButton = new QPushButton("LOAD GAME", this);
    loadButton->setStyleSheet(R"(
        QPushButton {
            font-size: 20px;
            color: white;
            border: 2.5px solid white;
            padding: 9px 78px;
            border-radius: 5px;
            background-color: transparent;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 50);
        }
    )");
    loadButton->setFont(regularFont);
    loadButton->setMinimumWidth(200);
    mainLayout->addWidget(loadButton);

    setLayout(mainLayout);

    connect(startButton, &QPushButton::clicked, this, &MenuInterface::switchToGameMenu);

    connect(loadButton, &QPushButton::clicked, this, []() {
        qDebug() << "Load Game button clicked!";
        });

    setScaledBackground();
}

void MenuInterface::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        emit exitApplication();
    }
    else {
        QWidget::keyPressEvent(event);
    }
}

void MenuInterface::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    setScaledBackground();
}

void MenuInterface::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    setScaledBackground();
}

void MenuInterface::setScaledBackground() {
    QPixmap background("resources/MainScreen.png");
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
