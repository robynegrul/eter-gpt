﻿#include "Board.h"

Board::Board(int boardSize) : size{ boardSize }, grid(boardSize, std::vector<card>(boardSize, { 0,0 })), firstCardPlaced{ false } {}

void Board::reset()
{
    grid.assign(size, std::vector<card>(size, { 0,0 }));
    firstCardPlaced = false;
}
bool Board::placeCard(int row, int col, card playCard)
{
    if (row >= 0 && row < size && col >= 0 && col < size) {
        int existingCard = grid[row][col].second;
        if (existingCard != 0 && firstCardPlaced && playCard.second > existingCard)
        {
            grid[row][col] = playCard;
            return true;
        }
        else if (isAdjacent(row, col) && firstCardPlaced)
        {
            if (existingCard == 0) {
                grid[row][col] = playCard;
                return true;
            }
        }
        else if (firstCardPlaced == false)
        {
            grid[row][col] = playCard;
            firstCardPlaced = true;
            return true;
        }
    }

    else if (firstCardPlaced == true && isAdjacent(row, col))
    {
        if (!fixedGridRows() && !fixedGridColumns())
        {
            if (row < 0 && col < 0 && row == col) {
                shiftRows(row, col);
                shiftColumns(row, col);
                grid[row][col] = playCard;
                return true;
            }
            else if (row >= size && col >= size && size == col) {
                shiftRows(row, col);
                shiftColumns(row, col);
                grid[row][col] = playCard;
                return true;
            }
            else if (row < 0 && col >= size && row + col == size - 1) {
                shiftRows(row, col);
                shiftColumns(row, col);
                grid[row][col] = playCard;
                return true;
            }
            else if (row >= size && col < 0 && row + col == size - 1) {
                shiftRows(row, col);
                shiftColumns(row, col);
                grid[row][col] = playCard;
                return true;
            }
        }
        else
        {
            if (fixedGridRows() && fixedGridColumns())
            {
                std::cerr << "Error: Cannot shift grid diagonally as there is at least one element in each row or column" << std::endl;
                return false;
            }
        }

        if ((row < 0 || row >= size) && !fixedGridRows() && (col >= 0 && col < size))
        {
            shiftRows(row, col);
            grid[row][col] = playCard;
            return true;
        }
        if ((col < 0 || col >= size) && !fixedGridColumns() && (row >= 0 && row < size))
        {
            shiftColumns(row, col);
            grid[row][col] = playCard;
            return true;
        }
    }
    return false;
}

bool Board::shiftGrid(int& row, int& col) {
    bool shifted = false;

    if (row < 0) {
        grid.insert(grid.begin(), std::vector<card>(size, { 0,0 }));
        grid.pop_back();
        row = 0;
        shifted = true;
    }
    else if (row >= size) {
        grid.push_back(std::vector<card>(size, { 0,0 }));
        grid.erase(grid.begin());
        row = size - 1;
        shifted = true;
    }

    if (col < 0) {
        for (auto& r : grid) {
            r.insert(r.begin(), { 0, 0 });
            r.pop_back();
        }
        col = 0;
        shifted = true;
    }
    else if (col >= size) {
        for (auto& r : grid) {
            r.push_back({ 0,0 });
            r.erase(r.begin());
        }
        col = size - 1;
        shifted = true;
    }

    if (!fixedGridRows() || !fixedGridColumns()) {
        if (row < 0 && col < 0 && row == col) {
            grid.insert(grid.begin(), std::vector<card>(size, { 0,0 }));
            grid.pop_back();
            for (auto& r : grid) {
                r.insert(r.begin(), { 0, 0 });
                r.pop_back();
            }
            row = 0;
            col = 0;
            shifted = true;
        }
        else if (row >= size && col >= size && size == col) {
            grid.push_back(std::vector<card>(size, { 0,0 }));
            grid.erase(grid.begin());
            for (auto& r : grid) {
                r.push_back({ 0,0 });
                r.erase(r.begin());
            }
            row = size - 1;
            col = size - 1;
            shifted = true;
        }

        else if (row < 0 && col >= size && row + col == size - 1) {
            grid.insert(grid.begin(), std::vector<card>(size, { 0,0 }));
            grid.pop_back();
            for (auto& r : grid) {
                r.push_back({ 0,0 });
                r.erase(r.begin());
            }
            row = 0;
            col = size - 1;
            shifted = true;
        }
        else if (row >= size && col < 0 && row + col == size - 1) {
            grid.push_back(std::vector<card>(size, { 0,0 }));
            grid.erase(grid.begin());
            for (auto& r : grid) {
                r.insert(r.begin(), { 0,0 });
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

void Board::shiftRows(int& row, int& col)
{
    if (row < 0) {
        grid.insert(grid.begin(), std::vector<card>(size, { 0,0 }));
        grid.pop_back();
        row = 0;
    }
    else if (row >= size) {
        grid.push_back(std::vector<card>(size, { 0,0 }));
        grid.erase(grid.begin());
        row = size - 1;
    }
}

void Board::shiftColumns(int& row, int& col)
{
    if (col < 0) {
        for (auto& r : grid) {
            r.insert(r.begin(), { 0,0 });
            r.pop_back();
        }
        col = 0;
    }
    else if (col >= size) {
        for (auto& r : grid) {
            r.push_back({ 0,0 });
            r.erase(r.begin());
        }
        col = size - 1;
    }
}

bool Board::fixedGridRows() const
{
    for (const auto& row : grid) {
        bool hasElement = false;
        for (const auto& cell : row) {
            if (cell.second != 0) {
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
    for (int col = 0; col < size; ++col) {
        bool hasElement = false;
        for (int row = 0; row < size; ++row) {
            if (grid[row][col].second != 0) {
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

bool Board::isAdjacent(int row, int col) const
{
    int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
    for (auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size && grid[newRow][newCol].second != 0) {
            return true;
        }
    }
    return false;
}
int Board::getSize() const
{
    return size;
}

card Board::getCard(int row, int col) const
{
    return grid[row][col];
}

bool Board::isFull() const
{
    for (const auto& row : grid)
    {
        for (const auto& cell : row)
        {
            if (cell.second == 0) // If there is an empty space
                return false;
        }
    }
    return true;
}

bool Board::checkWinCondition(int playerId) const
{
    for (int i = 0; i < size; ++i) {
        if (checkRow(i, playerId) || checkColumn(i, playerId))
            return true;
    }
    return checkDiagonals(playerId);
}

void Board::display() const
{
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << (cell.second == 0 ? " " : std::to_string(cell.first)) << " ";
        }
        std::cout << "\n";
    }
}

bool Board::checkRow(int row, int playerId) const
{
    for (int col = 0; col < size; ++col) {
        if (grid[row][col].first != playerId)
            return false;
    }
    return true;
}

bool Board::checkColumn(int col, int playerId) const
{
    for (int row = 0; row < size; ++row) {
        if (grid[row][col].first != playerId)
            return false;
    }
    return true;
}

bool Board::checkDiagonals(int playerId) const
{
    bool mainDiagonal = true;
    bool secondaryDiagonal = true;

    for (int i = 0; i < size; ++i) {
        if (grid[i][i].first != playerId) {
            mainDiagonal = false;
        }
        if (grid[i][size - i - 1].first != playerId) {
            secondaryDiagonal = false;
        }

        if (!mainDiagonal && !secondaryDiagonal) {
            return false;
        }
    }

    return mainDiagonal || secondaryDiagonal;
}
