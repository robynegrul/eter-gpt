#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "ExplosionPattern.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using card = std::pair<int, int>;

enum class PlaceCardResult {
	Success,
	Failure,
	CardLost
};

enum class ExplosionEffect {
	RemoveCard,
	CreateHole,
	TakeHand
};

struct Explosion {
	std::vector<card> affectedPositions;
	std::vector<ExplosionEffect> effects;
};

class Board {
private:
	std::vector<std::vector<card>> grid;
	int size;
	bool firstCardPlaced;
	std::vector<card>illusionPositions;
	std::map<card, int> illusionCards;

public:
	Board(int boardSize);
	void Reset();
	PlaceCardResult PlaceCard(int row, int col, card PlayCard);
	bool CheckWinCondition(int playerId) const;
	void Display() const;
	bool IsAdjacent(int row, int col) const;
	int CalculateCardValueSum(int playerId) const;
	bool IsFull() const;
	bool PlaceIllusion(int row, int col, int playerId, int cardValue);
	bool IsIllusion(int row, int col) const;
	bool CanActivateExplosion() const;
	void ActivateExplosion(Player& player);

private:
	bool CheckRow(int row, int playerValue) const;
	bool CheckColumn(int col, int playerValue) const;
	bool CheckDiagonals(int playerValue) const;
	bool ShiftGrid(int& row, int& col);
	bool FixedGridRows() const;
	bool FixedGridColumns() const;
	void ApplyExplosionEffects(const Explosion& explosion, Player& player);
};

#endif