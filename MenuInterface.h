#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QFontDatabase>
#include <QVBoxLayout>
#include <QShowEvent>


class MenuInterface : public QWidget
{
    Q_OBJECT

public:
    explicit MenuInterface(QWidget* parent = nullptr);
    ~MenuInterface();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    void setupUi();
    void setScaledBackground();

    QPushButton* startButton;
    QPushButton* loadButton;
    QVBoxLayout* layout;

signals:
    void switchToGameMenu();
    void exitApplication();
};

#endif 
