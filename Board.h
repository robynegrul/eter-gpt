
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>


using card = std::pair<int, int>;

class Board {
private:
    std::vector<std::vector<card>> grid;
    std::vector<std::vector<bool>> isIllusion;
    int size;
    bool firstCardPlaced;

public:
    Board(int boardSize);

    bool placeCard(int row, int col, card playCard, bool isIllusionCard = false);
    bool tryCoverCard(int row, int col, card opponentCard);
    void revealCard(int row, int col);//adaugare
    bool checkWinCondition(int playerId) const;

    void reset();
    void display() const;
    bool isAdjacent(int row, int col) const;
    int getSize() const;//adaugare
    card getCard(int row, int col) const;//adaugare
    bool isFull() const;

    bool shiftGrid(int& row, int& col);
    void shiftRows(int& row, int& col);
    void shiftColumns(int& row, int& col);
    bool fixedGridRows() const;
    bool fixedGridColumns() const;

private:
    bool checkRow(int row, int playerId) const;
    bool checkColumn(int col, int playerId) const;
    bool checkDiagonals(int playerId) const;
};

#endif 
