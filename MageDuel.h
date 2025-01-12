#pragma once
#ifndef MAGEDUEL_H
#define MAGEDUEL_H

#include "Board.h"
#include "GameModeStrategy.h"
#include <iostream>
//commit
#include <vector>
#include <string>

enum class MageType {
    Fire,
    Earth,
    Air,
    Water
};

struct MageCard {
    MageType type;               
    std::string face1Power;     
    std::string face2Power;      

    MageCard() : type(MageType::Fire), face1Power(""), face2Power("") {}
    MageCard(MageType type, const std::string& power1, const std::string& power2)
        : type(type), face1Power(power1), face2Power(power2) {
    }
};//commit



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
    void HandleMagicPower(Player& currentPlayer);//adaugat

    //adaugat 
    bool HandleFireMagePower(Player& currentPlayer);
    bool HandleEarthMagePower(Player& currentPlayer);
    bool HandleAirMagePower(Player& currentPlayer);
    bool HandleWaterMagePower(Player& currentPlayer);
    std::string MageTypeToString(MageType type); 
    //

private:
    int player1Wins, player2Wins;
    int currentPlayerId, winnerId;
    bool explosionTriggered, explosionExpired;
    bool firstCardPlaced;
    bool player1UsedIllusion, player2UsedIllusion;
    bool player1UsedMagic, player2UsedMagic;//adaugat

    Board board;                      
    Player player1, player2;   
    //adaugat
    std::vector<MageCard> mageCards;  
    MageCard player1MageCard;         
    MageCard player2MageCard;        
    std::string player1ActivePower;   
    std::string player2ActivePower;   
    //adaugat
};

#endif
