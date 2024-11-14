#include "Player.h"

Player::Player(int playerId) : id{ playerId }, initialCards{ { 1,1,2,2,3,3,4 } }, cards{ initialCards } {}

int Player::getId() const
{
    return id;

}

bool Player::playCard(int cardValue)
{
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (*it == cardValue) {
            cards.erase(it);
            return true;
        }
    }
    return false;
}

void Player::resetCards()
{
    cards = initialCards;
}

bool Player::hasCardsLeft() const
{
    return !cards.empty();
}


void Player::displayAvailableCards() const
{
    std::cout << "Cartile disponibile pentru Jucatorul " << id << ": ";
    for (int card : cards) {
        std::cout << card << " ";
    }
    std::cout << "\n";
}

