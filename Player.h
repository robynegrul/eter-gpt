#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>

class Player
{
private:
	int id;
	std::vector<int> cards;
	const std::vector<int> initialCards;

public:
	Player(int playerId);
	int GetId() const;
	bool PlayCard(int cardValue);
	void ResetCards();
	bool HasCardsLeft() const;
	bool HasCard(int cardValue) const;
	void DisplayAvailableCards() const;
	void AddCard(int cardValue);
};
#endif
