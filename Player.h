#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <algorithm>
#include <vector>

class Player
{
private:
	int id;
	std::vector<int> cards;
	const std::vector<int> initialCards;
	const std::vector<int> extendedInitialCards;
	card lastCardPlayed;

public:
	Player(int playerId);
	Player(const Player& other);
	int GetId() const;
	void ResetCards(int gameMode);
	void AddCard(int cardValue);
	void DisplayAvailableCards() const;
	bool PlayCard(int cardValue);
	bool HasCard(int cardValue) const;

private:
	Player& operator=(const Player& other);
	bool HasCardsLeft() const;
};
#endif
