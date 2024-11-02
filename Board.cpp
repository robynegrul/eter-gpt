//commit 
#include "Board.h"

Board::Board(int boardSize) : size(boardSize), grid(boardSize, std::vector<int>(boardSize, 0)) {}

void Board::reset()
{
    grid.assign(size, std::vector<int>(size, 0));
}//commit 

//commit 
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
}

bool Board::checkWinCondition(int playerValue) const
{
    // Verifică linii și coloane
    for (int i = 0; i < size; ++i) {
        if (checkRow(i, playerValue) || checkColumn(i, playerValue))
            return true;
    }
    // Verifică diagonale
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
}

bool Board::checkColumn(int col, int playerValue) const
{
    for (int row = 0; row < size; ++row) {
        if (grid[row][col] != playerValue)
            return false;
    }
    return true;
}

bool Board::checkDiagonals(int playerValue) const
{
    bool diag1 = true, diag2 = true;
    for (int i = 0; i < size; ++i) {
        diag1 &= (grid[i][i] == playerValue);
        diag2 &= (grid[i][size - i - 1] == playerValue);
    }
    return diag1 || diag2;
}//commit 