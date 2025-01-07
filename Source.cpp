#include <QApplication>
#include <QStackedWidget>
#include "MenuInterface.h"
#include "SelectGameModeInterface.h"
#include "TrainingInterface.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MenuInterface* menu = new MenuInterface();
	SelectGameModeInterface* selectGameMode = new SelectGameModeInterface();

	QStackedWidget stackedWidget;
	stackedWidget.addWidget(menu);
	stackedWidget.addWidget(selectGameMode);
	stackedWidget.showFullScreen();

	QObject::connect(menu, &MenuInterface::switchToGameMenu, [&]() {
		stackedWidget.setCurrentWidget(selectGameMode);
		});

	QObject::connect(selectGameMode, &SelectGameModeInterface::switchToMenu, [&]() {
		stackedWidget.setCurrentWidget(menu);
		});


	TrainingInterface* trainingInterface = new TrainingInterface();
	stackedWidget.addWidget(trainingInterface);
	QObject::connect(menu, &MenuInterface::exitApplication, &app, &QApplication::quit);
	QObject::connect(selectGameMode, &SelectGameModeInterface::exitApplication, &app, &QApplication::quit);
	QObject::connect(trainingInterface, &TrainingInterface::exitApplication, &app, &QApplication::quit);

	QObject::connect(selectGameMode, &SelectGameModeInterface::switchToTraining, [&]() {
		stackedWidget.setCurrentWidget(trainingInterface);
		});
	return app.exec();
}