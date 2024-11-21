#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <map>

using card = std::pair<int, int>;

//adaugare enum
enum class PlaceCardResult {
    Success,
    Failure,
    CardLost
};

class Board
{
private:
    std::vector<std::vector<card>> grid;
    //eliminare
    int size;
    bool firstCardPlaced;
    std::vector<std::pair<int, int>> illusionPositions; //adaugare
    std::map<std::pair<int, int>, int> illusionCards; //adaugare


public:
    Board(int boardSize);

    PlaceCardResult placeCard(int row, int col, card playCard);//modificare functie inclus tip

    bool checkWinCondition(int playerId) const;

    void reset();

    void display() const;

    bool isAdjacent(int row, int col) const;

    int calculateCardValueSum(int playerId) const; //adaugare

    bool isFull() const;

    bool placeIllusion(int row, int col, int playerId, int cardValue);//adaugare

    bool revealIllusion(int row, int col, int opponentCardValue, int& illusionCardValue);//adaugare

    bool isIllusion(int row, int col) const;//adaugare

    //eliminare cateva functii

private:
    bool checkRow(int row, int playerId) const;

    bool checkColumn(int col, int playerId) const;

    bool checkDiagonals(int playerId) const;

    bool shiftGrid(int& row, int& col);
    void shiftRows(int& row, int& col);
    void shiftColumns(int& row, int& col);
    bool fixedGridRows() const;
    bool fixedGridColumns() const;

};

#endif
