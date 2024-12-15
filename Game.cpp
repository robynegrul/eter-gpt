#include "Game.h"

Game::Game() : currentMode(nullptr) {}
//sterge if si foloseste switch - commit
void Game::SetGameMode(int choice) {
    switch (choice) {
    case 1:
        currentMode = std::make_unique<TrainingMode>();
        break;
    case 2:
        currentMode = std::make_unique<MageDuel>();
        break;
    case 3:
        currentMode = std::make_unique<ElementalBattle>();
        break;
    case 4:
        currentMode = std::make_unique<SpeedMode>();
        break;
    default:
        std::cout << "Selecție invalidă!\n";
        return;
    }
}

void Game::StartGame() {
    //currentMode, nu CurrentMode, schimba nume variabila
    if (currentMode) {
        currentMode->StartGame();
    }
    else {
        std::cout << "No game mode selected.\n";
    }
}