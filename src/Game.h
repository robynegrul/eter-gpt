#pragma once

#include "GameModeStrategy.h"
#include "TrainingMode.h"
#include "MageDuel.h"
#include "ElementalBattle.h"
#include "SpeedMode.h"
#include <iostream>

class Game {

public:
    Game();
    void StartGame();
    void SetGameMode(int choice);

private:
    std::unique_ptr<GameModeStrategy> currentMode;
};
