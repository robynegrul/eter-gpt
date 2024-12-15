#include "Game.h"

Game::Game() : currentMode(nullptr) {}
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
    if (currentMode) {
        currentMode->StartGame();
    }
    else {
        std::cout << "No game mode selected.\n";
    }
}