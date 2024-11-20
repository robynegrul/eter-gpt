
#include "Player.h"

Player::Player(int playerId)
    : id{ playerId }, initialCards{ { 1, 1, 2, 2, 3, 3, 4 } }, cards{ initialCards }, illusionUsed{ false } {
}

int Player::getId() const {
    return id;
}

bool Player::playCard(int cardValue) {
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (*it == cardValue) {
            cards.erase(it);
            return true;
        }
    }
    return false;
}

void Player::resetCards() {
    cards = initialCards;
    illusionUsed = false; 
}

bool Player::hasCardsLeft() const {
    return !cards.empty();
}

void Player::displayAvailableCards() const {
    std::cout << "Available cards for Player " << id << ": ";
    for (auto card : cards) {
        std::cout << card << " ";
    }
    std::cout << "\n";
}

void Player::addCard(int cardValue) {
    cards.push_back(cardValue);
}

bool Player::hasCard(int cardValue) const {
    for (int card : cards) {
        if (card == cardValue) {
            return true;
        }
    }
    return false;
}
