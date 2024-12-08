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
	const std::vector<int> extendedInitialCards;//adaugare

public:
	Player(int playerId);
	Player(const Player& other);//adaugare
	Player& operator=(const Player& other);//adaugare
	int GetId() const;
	bool PlayCard(int cardValue);
	void ResetCards(int gameMode);//adaugare parametru
	bool HasCardsLeft() const;
	bool HasCard(int cardValue) const;
	void DisplayAvailableCards() const;
	void AddCard(int cardValue);
};
#endif
