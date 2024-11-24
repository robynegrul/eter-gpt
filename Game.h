#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    int player1Wins;
    int player2Wins;
    int currentPlayerId;
    bool firstCardPlaced;//
    bool player1UsedIllusion;//
    bool player2UsedIllusion;//
    bool explosionTriggered;//

public:
    Game();
    void start();
    void playRound();
    void resetRound();
    void displayScore() const;
    //eliminare functii
};

#endif
