#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>

#define card std::pair<int, int>

class Board
{
private:
    std::vector<std::vector<card>> grid;
    int size;
    bool firstCardPlaced;

public:
    Board(int boardSize);

    bool placeCard(int row, int col, card playCard);

    bool checkWinCondition(int playerId) const;

    void reset();

    void display() const;

    bool isAdjacent(int row, int col) const;

    int getSize() const;

    card getCard(int row, int col) const;

    bool isFull() const;

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

#endif BOARD_H
