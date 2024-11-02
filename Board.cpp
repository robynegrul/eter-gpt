//commit 
#include "Board.h"

Board::Board(int boardSize) : size(boardSize), grid(boardSize, std::vector<int>(boardSize, 0)) {}

void Board::reset()
{
    grid.assign(size, std::vector<int>(size, 0));
}
bool Board::placeCard(int row, int col, int cardValue)
{
    if (row >= 0 && row < size && col >= 0 && col < size) {
        int existingCard = grid[row][col];
        if (existingCard == 0 || cardValue > existingCard) { 
            grid[row][col] = cardValue;
            return true;
        }
    }
    return false;
}//commit

//commit
bool Board::checkWinCondition(int playerValue) const
{
    for (int i = 0; i < size; ++i) {
        if (checkRow(i, playerValue) || checkColumn(i, playerValue))
            return true;
    }
    return checkDiagonals(playerValue);
}//commit 

//commit 
void Board::display() const
{
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell == 0 ? "." : std::to_string(cell)) << " ";
        }
        std::cout << "\n";
    }
}//commit 

//commit 
bool Board::checkRow(int row, int playerValue) const
{
    for (int col = 0; col < size; ++col) {
        if (grid[row][col] != playerValue)
            return false;
    }
    return true;
}//commit

//commit
bool Board::checkColumn(int col, int playerValue) const
{
    for (int row = 0; row < size; ++row) {
        if (grid[row][col] != playerValue)
            return false;
    }
    return true;
}//commit

  //commit

bool Board::checkDiagonals(int playerValue) const
{
    bool mainDiagonal = true;
    bool secondaryDiagonal = true;

    for (int i = 0; i < size; ++i) {
        if (grid[i][i] != playerValue) {
            mainDiagonal = false;
        }
        if (grid[i][size - i - 1] != playerValue) {
            secondaryDiagonal = false;
        }
        // Dacă ambele sunt false, ieșim din buclă
        if (!mainDiagonal && !secondaryDiagonal) {
            return false;
        }
    }

    return mainDiagonal || secondaryDiagonal;
}
//commit 