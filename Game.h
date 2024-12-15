#pragma once
#ifndef GAME_H
#define GAME_H

#include "GameModeStrategy.h"
#include "TrainingMode.h"
#include "MageDuel.h"
#include "ElementalBattle.h"
#include "SpeedMode.h"//adauga
#include <iostream>

class Game {

public:
    Game();
    void StartGame();
    void SetGameMode(int choice);

private:
    std::unique_ptr<GameModeStrategy> currentMode;//nu cu C, cu c mic
};

#endif