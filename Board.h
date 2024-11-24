#ifndef BOARD_H
#define BOARD_H
//adaugare includes
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include "Player.h"
#include "ExplosionPattern.h"

using card = std::pair<int, int>;
//commit
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
    std::vector<std::pair<int, int>> affectedPositions;
    std::vector<ExplosionEffect> effects;
};//commit

class Board {
private:
    std::vector<std::vector<card>> grid;
    //eliminare
    int size;
    bool firstCardPlaced;
    std::vector<std::pair<int, int>> illusionPositions;//adaugare
    std::map<std::pair<int, int>, int> illusionCards;//adaugare

public:
    Board(int boardSize);

    void reset();

    PlaceCardResult placeCard(int row, int col, card playCard);//modificare tip functie

    bool checkWinCondition(int playerId) const;

    void display() const;

    bool isAdjacent(int row, int col) const;

    //eliminare 2 functii

    int calculateCardValueSum(int playerId) const;//adaugare

    bool isFull() const;

    bool placeIllusion(int row, int col, int playerId, int cardValue);//adaugare

    bool isIllusion(int row, int col) const;//adaugare

    bool canActivateExplosion(int playerId) const;//adaugare

    void activateExplosion(int playerId, Player& player1, Player& player2);//adaugare

    void findLastPlacedCard(int playerId, int& row, int& col) const;//adaugare

    //eliminare functii ai grija

private:
    bool checkRow(int row, int playerId) const;

    bool checkColumn(int col, int playerId) const;

    bool checkDiagonals(int playerId) const;

    bool shiftGrid(int& row, int& col);//muta la privat

    bool fixedGridRows() const;//muta la privat

    bool fixedGridColumns() const;//muta la privat

    void applyExplosionEffects(const Explosion& explosion);//adaugare

    Explosion generateExplosionEffects(int explosionRow, int rotation = -1);//adaugare
};

#endif
