#pragma once
#ifndef TRAININGMODE_H
#define TRAININGMODE_H

#include "Board.h"
#include "GameModeStrategy.h"
#include "Player.h"
#include <iostream>

class TrainingMode : public GameModeStrategy {
public:
    void StartGame() override;
    void ResetRound() override;
    void PlayRound() override;
    void DisplayScore() const override;
    void ShowAvailableModes() const override;
    TrainingMode();

private:

    void HandleExplosion(Player& currentPlayer, Player& otherPlayer);
    void HandleIllusion(Player& currentPlayer);
    void HandleDrawOrWinner();
    bool HandleCardSelection(Player& currentPlayer);
    bool HandleNormalCard(Player& currentPlayer, int cardValue);

private:
    int player1Wins, player2Wins;
    int currentPlayerId, winnerId;
    bool explosionTriggered, explosionExpired;
    bool firstCardPlaced;
    bool player1UsedIllusion, player2UsedIllusion;
    Board board;
    Player player1, player2;
};

#endif


