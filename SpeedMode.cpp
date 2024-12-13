#include "SpeedMode.h"
#include "TrainingMode.h"
#include "ElementalBattle.h"
#include "MageDuel.h"
#include <iostream>
#include <chrono>
#include <thread>

SpeedMode::SpeedMode() : currentMode(nullptr), roundDurationInSeconds(60) {}

void SpeedMode::ShowAvailableModes() const {
    std::cout << "Choose a game mode:\n";
    std::cout << "1. Training Mode\n";
    std::cout << "2. Elemental Battle\n";
    std::cout << "3. Mage Duel\n";
}

void SpeedMode::SetMode(int choice) {
    switch (choice) {
    case 1:
        currentMode = std::make_unique<TrainingMode>();
        break;
    case 2:
        currentMode = std::make_unique<ElementalBattle>();
        break;
    case 3:
        currentMode = std::make_unique<MageDuel>();
        break;
    default:
        std::cout << "Invalid choice!\n";
        return;
    }
}

void SpeedMode::StartGame() {
    ShowAvailableModes();

    int choice;
    std::cin >> choice;

    SetMode(choice);

    if (currentMode) {
        std::cout << "Game started in mode: " << choice << std::endl;
        std::cout << "Select round timer (60, 90, or 120 seconds): ";
        int timeChoice;
        std::cin >> timeChoice;
        SetTimer(timeChoice);
        PlayRoundWithTimer();
    }
}

void SpeedMode::SetTimer(int timeChoice) {
    switch (timeChoice) {
    case 60:
        roundDurationInSeconds = 60;
        break;
    case 90:
        roundDurationInSeconds = 90;
        break;
    case 120:
        roundDurationInSeconds = 120;
        break;
    default:
        std::cout << "Invalid time. Setting timer to 60 seconds.\n";
        roundDurationInSeconds = 60;
        break;
    }
}

void SpeedMode::PlayRoundWithTimer() {
    auto roundStartTime = std::chrono::steady_clock::now();

    bool roundInProgress = true;
    while (roundInProgress) {
        auto currentTime = std::chrono::steady_clock::now();
        auto timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - roundStartTime).count();

        int timeRemaining = roundDurationInSeconds - timeElapsed;

        if (timeRemaining <= 0) {
            std::cout << "Time's up! Round ended.\n";
            roundInProgress = false;
            return;
        }

        std::cout << "\rTime remaining: " << timeRemaining << " seconds   "; // \r pentru a suprascrie linia anterioară
        std::cout.flush(); // Asigură că textul este afisat

        if (currentMode) {
			currentMode->StartGame();
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void SpeedMode::ResetRound() {
    std::cout << "Round reset.\n";
}

void SpeedMode::PlayRound() {
    std::cout << "Game continues...\n";
}

void SpeedMode::DisplayScore() const {
    std::cout << "Displaying score...\n";
}
