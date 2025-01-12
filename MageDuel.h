#pragma once
#ifndef MAGEDUEL_H
#define MAGEDUEL_H

#include "Board.h"
#include "GameModeStrategy.h"
#include <iostream>
#include <vector>
#include <string>

enum class MageType {
    Fire,
    Earth,
    Air,
    Water
};

struct MageCard {
    MageType type;               // Tipul vrăjitorului
    std::string face1Power;      // Puterea de pe fața 1
    std::string face2Power;      // Puterea de pe fața 2

    MageCard() : type(MageType::Fire), face1Power(""), face2Power("") {}
    MageCard(MageType type, const std::string& power1, const std::string& power2)
        : type(type), face1Power(power1), face2Power(power2) {
    }
};



class MageDuel : public GameModeStrategy {
public:
    MageDuel();

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
    void HandleMagicPower(Player& currentPlayer);

    // Funcții pentru fiecare categorie de vrăjitori
    bool HandleFireMagePower(Player& currentPlayer);
    bool HandleEarthMagePower(Player& currentPlayer);
    bool HandleAirMagePower(Player& currentPlayer);
    bool HandleWaterMagePower(Player& currentPlayer);
    std::string MageTypeToString(MageType type); 

private:
    int player1Wins, player2Wins;
    int currentPlayerId, winnerId;
    bool explosionTriggered, explosionExpired;
    bool firstCardPlaced;
    bool player1UsedIllusion, player2UsedIllusion;
    bool player1UsedMagic, player2UsedMagic;

    // Instanțe și membri adăugați
    Board board;                      // Tablă de joc
    Player player1, player2;          // Jucători
    std::vector<MageCard> mageCards;  // Cărți de vrăjitori
    MageCard player1MageCard;         // Vrăjitorul jucătorului 1
    MageCard player2MageCard;         // Vrăjitorul jucătorului 2
    std::string player1ActivePower;   // Puterea activă a jucătorului 1
    std::string player2ActivePower;   // Puterea activă a jucătorului 2
};

#endif
