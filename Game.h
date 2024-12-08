#pragma once
#ifndef GAME_H
#define GAME_H

//modificare complet include uri

#include "GameModeStrategy.h"
#include "TrainingMode.h"
#include "MageDuel.h"
#include "ElementalBattle.h"
#include <iostream>

class Game {
    //eliminare variabile private
public:
    //eliminare toate functiile exceptie game si adaugare alte 2 functii noi
    Game();
    void StartGame();
    void SetGameMode(int choice);

    //adaugare var privata
private:
    std::unique_ptr<GameModeStrategy> CurrentMode;
};

#endif