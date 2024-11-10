﻿#ifndef BOARD_H
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

    //commit
    bool isAdjacent(int row, int col) const;
    //commit

private:
    bool checkRow(int row, int playerId) const;

    bool checkColumn(int col, int playerId) const;

    bool checkDiagonals(int playerId) const;

    bool shiftGrid(int& row, int& col);
    void shiftRows(int& row, int& col);
    void shiftColumns(int& row, int& col);
    //commituri in jos
    bool fixedGridRows() const;
    bool fixedGridColumns() const;
};

#endif BOARD_H
