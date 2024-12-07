#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

class Player
{
private:
	int id;
	std::vector<int> cards;
	const std::vector<int> initialCards;
	const std::vector<int> extendedInitialCards;

public:
	Player(int playerId);
	Player(const Player& other);
	Player& operator=(const Player& other);
	int GetId() const;
	bool PlayCard(int cardValue);
	void ResetCards(int gameMode);
	bool HasCardsLeft() const;
	bool HasCard(int cardValue) const;
	void DisplayAvailableCards() const;
	void AddCard(int cardValue);
};
#endif
