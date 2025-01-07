#ifndef TRAININGINTERFACE_H
#define TRAININGINTERFACE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QShowEvent>
#include <QResizeEvent>
#include <QPalette>
#include <QPixmap>
#include "Game.h"
#include "TrainingMode.h"

class TrainingInterface : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingInterface(QWidget* parent = nullptr);
    ~TrainingInterface();
    void startGame();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    void setupUi();
    void setScaledBackground();
    Game gameInstance;

signals:
    void exitApplication();
};

#endif