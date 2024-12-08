#include "Game.h"
#include "MageDuel.h"
#include <iostream>
//modificare constructor, eliminare aproape tot
Game::Game() : CurrentMode(nullptr) {}
//eliminare functii

//commit (poate 2 idk)
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
}//