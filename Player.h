#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>

class Player {
private:
    int id;
    std::vector<int> cards;
    const std::vector<int> initialCards;
    
public:
    Player(int playerId);

    int getId() const;

    bool playCard(int cardValue);

	void resetCards();

	bool hasCardsLeft() const;

    //commit
    void displayAvailableCards() const;
    //commit

};

#endif