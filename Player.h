#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>

class Player {
private:
    int id;
    std::vector<int> cards;
    const std::vector<int> initialCards;
    //eliminare var

public:
    Player(int playerId);

    int getId() const;

    bool playCard(int cardValue);

    void resetCards();

    bool hasCardsLeft() const;

    bool hasCard(int cardValue) const;//adaugare

    void displayAvailableCards() const;

    void addCard(int cardValue);//adaugare

    //eliminare 2 functii
};

#endif
