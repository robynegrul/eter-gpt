#pragma once
#ifndef ELEMENTALBATTLE_H
#define ELEMENTALBATTLE_H

#include "Board.h"
#include "GameModeStrategy.h"
#include "Player.h"
#include <iostream>
#include <random>

enum class ElementalPowerType {
    ControlledExplosion,
    Destruction,
    Flame,
    Fire,
    Ash,
    Spark,
    Squall,
    Gale,
    Hurricane,
    Gust,
    Mirage,
    Storm,
    Tide,
    Mist,
    Wave,
    Whirlpool,
    Blizzard,
    Waterfall,
    Support,
    Earthquake,
    Crumble,
    Border,
    Avalanche,
    Rock
};

struct ElementalPower {
    ElementalPowerType type;
    std::string description;
};

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

    void InitializePowerDeck();
    void ShuffleAndDrawPowers();
    bool UsePower(int powerIndex, Player& currentPlayer, Player& opponent);

private:
    int turnNumber;
    int player1Wins, player2Wins;
    int currentPlayerId, winnerId;
    bool explosionTriggered, explosionExpired;
    bool firstCardPlaced;
    bool player1UsedIllusion, player2UsedIllusion;
    Board board;
    Player player1, player2;
    std::vector<ElementalPower> powerDeck;
    std::vector<ElementalPower> activePowers;
};

#endif