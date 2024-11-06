#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>

class Board
{
private:
    std::vector<std::vector<int>> grid;
    int size;
	bool firstCardPlaced; //commit
    
public:
    Board(int boardSize);
    
    bool placeCard(int row, int col, int cardValue);

    bool checkWinCondition(int playerValue) const;

    void reset();

    void display() const;

    //commit
    bool isAdjacent(int row, int col) const;
    //commit

private:
    bool checkRow(int row, int playerValue) const;

    bool checkColumn(int col, int playerValue) const;

    bool checkDiagonals(int playerValue) const;
};

#endif
