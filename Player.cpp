#include "Player.h"
Player::Player(int playerId) : id{ playerId }, initialCards{ { 1,1,2,2,3,3,4 } }, cards{ initialCards } {}

int Player::GetId() const
{
	return id;
}

bool Player::PlayCard(int cardValue)
{
	for (auto it = cards.begin(); it != cards.end(); ++it) {
		if (*it == cardValue)
		{
			cards.erase(it);
			return true;
		}
	}
	return false;
}

void Player::ResetCards()
{
	cards = initialCards;
}

bool Player::HasCardsLeft() const
{
	return !cards.empty();
}

void Player::DisplayAvailableCards() const
{
	std::cout << "Available cards for Player" << id << ": ";
	for (int card : cards)
	{
		std::cout << card << " ";
	}
	std::cout << "\n";
}
bool Player::HasCard(int cardValue) const
{
	for (int card : cards)
		if (card == cardValue)
			return true;
	return false;
}

void Player::AddCard(int cardValue)
{
	cards.push_back(cardValue);
}