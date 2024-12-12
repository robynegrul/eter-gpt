#include "Game.h"

Game::Game() : CurrentMode(nullptr) {}

void Game::SetGameMode(int choice) {
    if (choice == 1) {
        CurrentMode = std::make_unique<TrainingMode>();
    }
    else if (choice == 2) {
        CurrentMode = std::make_unique<MageDuel>();
    }
    else if (choice == 3) {
        CurrentMode = std::make_unique<ElementalBattle>();
    }
}

void Game::StartGame() {
    if (CurrentMode) {
        CurrentMode->StartGame();
    }
    else {
        std::cout << "No game mode selected.\n";
    }
}