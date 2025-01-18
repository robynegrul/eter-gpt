#pragma once

#include "Board.h"
#include "GameModeStrategy.h"
#include "Player.h"
#include <iostream>
class ElementalBattle : public GameModeStrategy
{
public:
    ElementalBattle();

private:
    void HandleExplosion(Player& currentPlayer);
    void HandleIllusion(Player& currentPlayer);
    void HandleDrawOrWinner();
    void StartGame() override;
    void ResetRound() override;
    void PlayRound() override;
    void DisplayScore() const override;
    void ShowAvailableModes() const override;
    bool HandleCardSelection(Player& currentPlayer);
    bool HandleNormalCard(Player& currentPlayer, int cardValue);

    void HandeDestroyer(Player& currentPlayer, Player& otherPlayer);

    inline Player& GetCurrentPlayer() { return (currentPlayerId == 1) ? player1 : player2; }
    Player& GetOtherPlayer() { return (currentPlayerId == 1) ? player2 : player1; }

private:
    int player1Wins, player2Wins;
    int currentPlayerId, winnerId;
    bool explosionTriggered, explosionExpired;
    bool firstCardPlaced;
    bool player1UsedIllusion, player2UsedIllusion;
    Board board;
    Player player1, player2;
};