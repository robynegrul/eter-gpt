//creare header
#pragma once
#ifndef GAMEMODESTRATEGY_H
#define GAMEMODESTRATEGY_H

class GameModeStrategy {
public:
    virtual ~GameModeStrategy() = default;

    virtual void StartGame() = 0;
    virtual void ResetRound() = 0;
    virtual void PlayRound() = 0;
    virtual void DisplayScore() const = 0;
    virtual void ShowAvailableModes() const = 0;
};

#endif 
