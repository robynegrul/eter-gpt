#ifndef SELECTGAMEMODEINTERFACE_H
#define SELECTGAMEMODEINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QFontDatabase>
#include <QVBoxLayout>
#include <QShowEvent>

class SelectGameModeInterface : public QWidget
{
    Q_OBJECT

public:
    explicit SelectGameModeInterface(QWidget* parent = nullptr);
    ~SelectGameModeInterface();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    void setupUi();
    void setScaledBackground();

    QPushButton* Training;
    QPushButton* MageDuel;
    QPushButton* ElementalBattle;
    QPushButton* Tournament;
    QPushButton* TimeAttack;
    QPushButton* BackButton;
    QVBoxLayout* layout;

signals:
    void switchToMenu();
    void exitApplication();
};

#endif 
