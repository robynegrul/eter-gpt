//commit 
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
    
public:
    Board(int boardSize);

    bool placeCard(int row, int col, int cardValue);
    //commit 


    //commit 
    bool checkWinCondition(int playerValue) const;

    void reset();

    void display() const;

private:
    bool checkRow(int row, int playerValue) const;

    bool checkColumn(int col, int playerValue) const;

    bool checkDiagonals(int playerValue) const;
};

#endif//commit 
