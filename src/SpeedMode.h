#pragma once

#include "GameModeStrategy.h"
#include <memory>

class SpeedMode : public GameModeStrategy {
public:
    SpeedMode();
    void StartGame() override;
    void ResetRound() override;
    void PlayRound() override;
    void DisplayScore() const override;
    void ShowAvailableModes() const override;
    void SetMode(int choice);
    void PlayRoundWithTimer();
    void SetTimer(int timeChoice);

private:
    std::unique_ptr<GameModeStrategy> currentMode;
    int roundDurationInSeconds;
};