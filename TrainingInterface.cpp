#include "TrainingInterface.h"
#include <QDebug>

TrainingInterface::TrainingInterface(QWidget* parent) : QWidget(parent) {
	setupUi();
}

TrainingInterface::~TrainingInterface() {
}

void TrainingInterface::setupUi() {
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	setLayout(layout);
	setScaledBackground();
}

void TrainingInterface::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape) {
		emit exitApplication();
	}
	else {
		QWidget::keyPressEvent(event);
	}
}


void TrainingInterface::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	setScaledBackground();
}

void TrainingInterface::showEvent(QShowEvent* event) {
	QWidget::showEvent(event);
	setScaledBackground();
}

void TrainingInterface::setScaledBackground() {
	QPixmap background("resources/GameScreen.png");
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

void TrainingInterface::startGame() {
	gameInstance.SetGameMode(1); // 1 pentru Training Mode
	gameInstance.StartGame();
}