
#include "Player.h"

Player::Player(int playerId)//adaugare o variabila
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
    illusionUsed = false; //adaugare
}

bool Player::hasCardsLeft() const {
    return !cards.empty();
}

void Player::displayAvailableCards() const {
    std::cout << "Available cards for Player " << id << ": ";
    for (int card : cards) {
        std::cout << card << " ";
    }
    std::cout << "\n";
}

bool Player::canUseIllusion() const {//adaugare
    return !illusionUsed;
}

bool Player::useIllusion(int cardValue) {//commit - eu
    if (illusionUsed) {
        std::cout << "You have already used an illusion. Choose a regular card.\n";
        return false;
    }
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (*it == cardValue) {
            cards.erase(it);
            illusionUsed = true;
            return true;
        }
    }
    std::cout << "Card not available. Choose a valid card.\n";
    return false;
}//commit - eu
