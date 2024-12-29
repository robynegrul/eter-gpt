#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MenuInterface : public QWidget {
    Q_OBJECT

public:
    explicit MenuInterface(QWidget* parent = nullptr);

private:
    void setupMenu();
    void switchToNewGameScreen();
    void resetMenu();

    QVBoxLayout* layout;
};

#endif
