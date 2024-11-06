#include "Board.h"

Board::Board(int boardSize) : size(boardSize), grid(boardSize, std::vector<int>(boardSize, 0)), firstCardPlaced{ false } {}

void Board::reset()
{
    grid.assign(size, std::vector<int>(size, 0));
    firstCardPlaced = false;
}

bool Board::placeCard(int row, int col, int cardValue)
{
    if (row >= 0 && row < size && col >= 0 && col < size) {
        int existingCard = grid[row][col];
        if (isAdjacent(row, col) && firstCardPlaced == true)
        {
            if (existingCard == 0) {
                grid[row][col] = cardValue;
                return true;
            }
            else if (cardValue > existingCard) {
                grid[row][col] = cardValue;
                return true;
            }
        }
        else if (firstCardPlaced == false)
        {
            grid[row][col] = cardValue;
            firstCardPlaced = true;
            return true;
        }
    }
    else if (firstCardPlaced == true && isAdjacent(row, col))
    {
        if ((row < 0 || row >= size) && !fixedGridRows())
        {
            shiftGrid(row, col);
            grid[row][col] = cardValue;
            return true;
        }
        if ((col < 0 || col >= size) && !fixedGridColumns())
        {
            shiftGrid(row, col);
            grid[row][col] = cardValue;
            return true;
        }
    }
    return false;
}

bool Board::shiftGrid(int& row, int& col) {
    bool shifted = false;

    // Shift rows
    if (row < 0) {
        grid.insert(grid.begin(), std::vector<int>(size, 0));
        grid.pop_back();
        row = 0;
        shifted = true;
    }
    else if (row >= size) {
        grid.push_back(std::vector<int>(size, 0));
        grid.erase(grid.begin());
        row = size - 1;
        shifted = true;
    }

    // Shift columns
    if (col < 0) {
        for (auto& r : grid) {
            r.insert(r.begin(), 0);
            r.pop_back();
        }
        col = 0;
        shifted = true;
    }
    else if (col >= size) {
        for (auto& r : grid) {
            r.push_back(0);
            r.erase(r.begin());
        }
        col = size - 1;
        shifted = true;
    }

    // Diagonal shifts
    if (!fixedGridRows() && !fixedGridColumns()) {
        if (row < 0 && col < 0) {
            grid.insert(grid.begin(), std::vector<int>(size, 0));
            grid.pop_back();
            for (auto& r : grid) {
                r.insert(r.begin(), 0);
                r.pop_back();
            }
            row = 0;
            col = 0;
            shifted = true;
        }
        else if (row >= size && col >= size) {
            grid.push_back(std::vector<int>(size, 0));
            grid.erase(grid.begin());
            for (auto& r : grid) {
                r.push_back(0);
                r.erase(r.begin());
            }
            row = size - 1;
            col = size - 1;
            shifted = true;
        }
        else if (row < 0 && col >= size) {
            grid.insert(grid.begin(), std::vector<int>(size, 0));
            grid.pop_back();
            for (auto& r : grid) {
                r.push_back(0);
                r.erase(r.begin());
            }
            row = 0;
            col = size - 1;
            shifted = true;
        }
        else if (row >= size && col < 0) {
            grid.push_back(std::vector<int>(size, 0));
            grid.erase(grid.begin());
            for (auto& r : grid) {
                r.insert(r.begin(), 0);
                r.pop_back();
            }
            row = size - 1;
            col = 0;
            shifted = true;
        }
    }
    else {
        std::cerr << "Error: Cannot shift grid diagonally as there is at least one element in each row or column" << std::endl;
    }

    return shifted;
}

bool Board::fixedGridRows() const
{
    // Check if there is at least one element in each row
    for (const auto& row : grid) {
        bool hasElement = false;
        for (int cell : row) {
            if (cell != 0) {
                hasElement = true;
                break;
            }
        }
        if (!hasElement) {
            return false;
        }
    }
    return true;
}

bool Board::fixedGridColumns() const
{
    // Check if there is at least one element in each column
    for (int col = 0; col < size; ++col) {
        bool hasElement = false;
        for (int row = 0; row < size; ++row) {
            if (grid[row][col] != 0) {
                hasElement = true;
                break;
            }
        }
        if (!hasElement) {
            return false;
        }
    }
    return true;
}

bool Board::checkWinCondition(int playerValue) const
{
    for (int i = 0; i < size; ++i) {
        if (checkRow(i, playerValue) || checkColumn(i, playerValue))
            return true;
    }
    return checkDiagonals(playerValue);
}

void Board::display() const
{
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell == 0 ? "." : std::to_string(cell)) << " ";
        }
        std::cout << "\n";
    }
}

bool Board::isAdjacent(int row, int col) const
{
    int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
    for (auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size && grid[newRow][newCol] != 0) {
            return true;
        }
    }
    return false;
}

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
    bool mainDiagonal = true;
    bool secondaryDiagonal = true;

    for (int i = 0; i < size; ++i) {
        if (grid[i][i] != playerValue) {
            mainDiagonal = false;
        }
        if (grid[i][size - i - 1] != playerValue) {
            secondaryDiagonal = false;
        }

        if (!mainDiagonal && !secondaryDiagonal) {
            return false;
        }
    }

    return mainDiagonal || secondaryDiagonal;
}
