#pragma once

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

	int m_LastCard;

public:
	Player(int playerId);
	Player(const Player& other);
	int GetId() const;
	void ResetCards(int gameMode);
	void AddCard(int cardValue);
	void DisplayAvailableCards() const;
	bool PlayCard(int cardValue);
	bool HasCard(int cardValue) const;

	void RemoveCard(int cardValue);
	inline int GetLastCard() const { return m_LastCard; }

private:
	Player& operator=(const Player& other);
	bool HasCardsLeft() const;
};
