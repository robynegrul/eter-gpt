#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <map>

using card = std::pair<int, int>;

enum class PlaceCardResult {
    Success,
    Failure,
    CardLost
};

class Board
{
private:
    std::vector<std::vector<card>> grid;
    int size;
    bool firstCardPlaced;
    std::vector<std::pair<int, int>> illusionPositions; // To store positions of illusions
    std::map<std::pair<int, int>, int> illusionCards;   // Map to store the card values of illusions


public:
    Board(int boardSize);

    PlaceCardResult placeCard(int row, int col, card playCard);//

    bool checkWinCondition(int playerId) const;

    void reset();

    void display() const;

    //commit
    bool isAdjacent(int row, int col) const;
    //commit
    int calculateCardValueSum(int playerId) const;

    bool isFull() const;

    bool placeIllusion(int row, int col, int playerId, int cardValue);

    bool revealIllusion(int row, int col, int opponentCardValue, int& illusionCardValue);

    bool isIllusion(int row, int col) const;

private:
    bool checkRow(int row, int playerId) const;

    bool checkColumn(int col, int playerId) const;

    bool checkDiagonals(int playerId) const;

    bool shiftGrid(int& row, int& col);
    //commituri in jos
    void shiftRows(int& row, int& col);
    void shiftColumns(int& row, int& col);
    bool fixedGridRows() const;
    bool fixedGridColumns() const;

};

#endif
