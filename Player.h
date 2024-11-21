#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>

class Player {
private:
    int id;
    std::vector<int> cards;
    const std::vector<int> initialCards;
    //eliminare

public:
    Player(int playerId);

    int getId() const;

    bool playCard(int cardValue);

    void resetCards();

    bool hasCardsLeft() const;

    bool hasCard(int cardValue) const; //adaugare

    void displayAvailableCards() const;
    //eliminare
    //eliminare
    void addCard(int cardValue);//adaugare
};

#endif
