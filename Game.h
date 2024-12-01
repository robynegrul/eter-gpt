#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

class Game
{
private:
	Board board;
	Player player1;
	Player player2;
	int player1Wins;
	int player2Wins;
	int currentPlayerId;
	int winnerId;
	bool firstCardPlaced;
	bool player1UsedIllusion;
	bool player2UsedIllusion;
	bool explosionTriggered;
	bool explosionExpired;

public:
	Game();
	void Start();
	void ResetRound();
	void DisplayScore() const;
	void PlayRound();
};

#endif