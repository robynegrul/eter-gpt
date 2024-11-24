#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "Player.h"
#include "ExplosionPattern.h"

using card = std::pair<int, int>;

enum class PlaceCardResult {
    Success,
    Failure,
    CardLost
};

enum class ExplosionEffect {
    RemoveCard,
    CreateHole
};

struct Explosion {
    std::vector<card> affectedPositions;
    std::vector<ExplosionEffect> effects;
};

class Board {
private:
    std::vector<std::vector<card>> grid;
    int size;
    bool firstCardPlaced;
    std::vector<card> illusionPositions;
    std::map<card, int> illusionCards;

public:
    Board(int boardSize);
    void reset();
    PlaceCardResult placeCard(int row, int col, card playCard);
    bool checkWinCondition(int playerId) const;
    void display() const;
    bool isAdjacent(int row, int col) const;
    int calculateCardValueSum(int playerId) const;
    bool isFull() const;
    bool placeIllusion(int row, int col, int playerId, int cardValue);
    bool isIllusion(int row, int col) const;
    bool canActivateExplosion(int playerId) const;
    void activateExplosion(int playerId, Player& player1, Player& player2);
    void findLastPlacedCard(int playerId, int& row, int& col) const;

private:
    bool checkRow(int row, int playerId) const;
    bool checkColumn(int col, int playerId) const;
    bool checkDiagonals(int playerId) const;

    bool shiftGrid(int& row, int& col);//muta la privat

    bool fixedGridRows() const;//muta la privat

    bool fixedGridColumns() const;//muta la privat

    void applyExplosionEffects(const Explosion& explosion);//adaugare

    
};

#endif