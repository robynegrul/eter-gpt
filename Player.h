#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <algorithm>
#include <vector>
//schimba ordine
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
	int GetId() const;
	void ResetCards(int gameMode);
	void AddCard(int cardValue);
	void DisplayAvailableCards() const;
	bool PlayCard(int cardValue);
	bool HasCard(int cardValue) const;

private:
	Player& operator=(const Player& other);//muta din public in private
	bool HasCardsLeft() const;
};
#endif
