#pragma once
#ifndef BOARD_H
#define BOARD_H

#include "ExplosionPattern.h"
#include "Player.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

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
	PlaceCardResult PlaceCard(int row, int col, card PlayCard);
	void Reset();
	void ActivateExplosion(Player& player, Player& other);
	void Display() const;
	bool CanActivateExplosion() const;
	bool PlaceIllusion(int row, int col, int playerId, int cardValue);
	bool CheckWinCondition(int playerId) const;
	bool IsFull() const;
	int CalculateCardValueSum(int playerId) const;

private:
	bool CheckRow(int row, int playerValue) const;
	bool CheckColumn(int col, int playerValue) const;
	bool CheckDiagonals(int playerValue) const;
	bool DiagonalShift(int& row, int& col);
	bool HorizontalShift(int& row, int& col);
	bool VerticalShift(int& row, int& col);
	bool ShiftGrid(int& row, int& col);
	bool FixedGridRows() const;
	bool FixedGridColumns() const;
	bool IsAdjacent(int row, int col) const;
	bool IsIllusion(int row, int col) const;
	bool IsIllusionValue(card cell) const;
	void ApplyExplosionEffects(const Explosion& explosion, Player& player, Player& other);
	void EliminateIllusions();
};

#endif