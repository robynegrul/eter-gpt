#include "Board.h"

Board::Board(int boardSize)
    : size(boardSize), grid(boardSize, std::vector<card>(boardSize, { 0, 0 })), firstCardPlaced(false) {
}

void Board::reset() {
    grid.assign(size, std::vector<card>(size, { 0, 0 }));
    firstCardPlaced = false;
}

bool Board::placeCard(int row, int col, card playCard) {
    // Only attempt to shift the grid if not all rows and columns are fixed
    if (!(fixedGridRows() && fixedGridColumns()) && shiftGrid(row, col) && isAdjacent(row, col)) {
        std::cout << "The grid has been shifted to accommodate the new position.\n";
    }

    // Proceed with the card placement logic
    if (row >= 0 && row < size && col >= 0 && col < size) {
        // Check if the position contains an illusion
        if (isIllusion(row, col)) {
            int illusionCardValue = illusionCards[{row, col}];

            // If the new card's value is greater, replace the illusion
            if (playCard.second > illusionCardValue) {
                grid[row][col] = playCard;
                illusionCards.erase({ row, col }); // Remove the illusion entry
                return true;
            }
            else {
                std::cout << "Your card is not greater than the illusion. You lose your card, and your turn is over.\n";
                return -1; // The card is lost, and the turn passes
            }
        }

        // If there is a regular card, only replace if the new card's value is greater or equal
        if (grid[row][col].second != 0) {
            if (playCard.second >= grid[row][col].second) {
                grid[row][col] = playCard;
                return true;
            }
            else {
                std::cout << "You cannot replace a card with a smaller one. Try again.\n";
                return false;
            }
        }

        // Check adjacency only if this is not the first card placed
        if (firstCardPlaced && !isAdjacent(row, col)) {
            std::cout << "The selected position is not adjacent to an existing card. Try again.\n";
            return false;
        }

        // Place the card on an empty spot
        grid[row][col] = playCard;
        if (!firstCardPlaced) {
            firstCardPlaced = true;
        }
        return true;
    }
    return false;
}

bool Board::shiftGrid(int& row, int& col) {
    bool shifted = false;
    if (row < 0) {
        grid.insert(grid.begin(), std::vector<card>(size, { 0, 0 }));
        grid.pop_back();
        row = 0;
        shifted = true;
    }
    else if (row >= size) {
        grid.push_back(std::vector<card>(size, { 0, 0 }));
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
            r.push_back({ 0, 0 });
            r.erase(r.begin());
        }
        col = size - 1;
        shifted = true;
    }
    return shifted;
}

void Board::shiftRows(int& row, int& col) {
    if (row < 0) {
        grid.insert(grid.begin(), std::vector<card>(size, { 0, 0 }));
        grid.pop_back();
        row = 0;
    }
    else if (row >= size) {
        grid.push_back(std::vector<card>(size, { 0, 0 }));
        grid.erase(grid.begin());
        row = size - 1;
    }
}

void Board::shiftColumns(int& row, int& col) {
    if (col < 0) {
        for (auto& r : grid) {
            r.insert(r.begin(), { 0, 0 });
            r.pop_back();
        }
        col = 0;
    }
    else if (col >= size) {
        for (auto& r : grid) {
            r.push_back({ 0, 0 });
            r.erase(r.begin());
        }
        col = size - 1;
    }
}

bool Board::fixedGridRows() const {
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

bool Board::fixedGridColumns() const {
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

bool Board::checkWinCondition(int playerId) const {
    for (int i = 0; i < size; ++i) {
        if (checkRow(i, playerId) || checkColumn(i, playerId)) {
            return true;
        }
    }
    return checkDiagonals(playerId);
}

void Board::display() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.second == 0) {
                std::cout << "[   ] "; // Empty cell
            }
            else if (cell.second == -1) {
                std::cout << "[" << cell.first << ",?] "; // Illusion
            }
            else {
                std::cout << "[" << cell.first << "," << cell.second << "] ";
                // cell.first is the playerID, cell.second is the cardValue
            }
        }
        std::cout << "\n";
    }
}

bool Board::isAdjacent(int row, int col) const {
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

bool Board::checkRow(int row, int playerId) const {
    for (int col = 0; col < size; ++col) {
        if (grid[row][col].first != playerId) {
            return false;
        }
    }
    return true;
}

bool Board::checkColumn(int col, int playerId) const {
    for (int row = 0; row < size; ++row) {
        if (grid[row][col].first != playerId) {
            return false;
        }
    }
    return true;
}

bool Board::checkDiagonals(int playerId) const {
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

int Board::calculateCardValueSum(int playerId) const {
    int sum = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.first == playerId) {
                sum += cell.second; // Add the cardValue if it belongs to the player
            }
        }
    }
    return sum;
}

bool Board::isFull() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.second == 0) { // Check if there's any empty cell
                return false;
            }
        }
    }
    return true;
}

bool Board::placeIllusion(int row, int col, int playerId, int cardValue) {
    if (!(fixedGridRows() && fixedGridColumns()) && shiftGrid(row, col) && isAdjacent(row, col)) {
        std::cout << "The grid has been shifted to accommodate the new position.\n";
    }

    if (row >= 0 && row < size && col >= 0 && col < size && grid[row][col].second == 0) {
        // Enforce adjacency rules if this is not the first card placed
        if (firstCardPlaced && !isAdjacent(row, col)) {
            std::cout << "The selected position is not adjacent to an existing card. Try again.\n";
            return false;
        }

        illusionPositions.push_back({ row, col });
        illusionCards[{row, col}] = cardValue;
        grid[row][col] = { playerId, -1 }; // Use -1 to indicate an illusion

        // Set firstCardPlaced to true if this is the first placement
        if (!firstCardPlaced) {
            firstCardPlaced = true;
        }
        return true;
    }
    return false;
}

bool Board::revealIllusion(int row, int col, int opponentCardValue, int& illusionCardValue) {
    if (illusionCards.count({ row, col }) > 0) {
        illusionCardValue = illusionCards[{row, col}];
        grid[row][col].second = illusionCardValue; // Reveal the illusion
        return illusionCardValue >= opponentCardValue;
    }
    return false;
}

bool Board::isIllusion(int row, int col) const {
    return std::find(illusionPositions.begin(), illusionPositions.end(), std::make_pair(row, col)) != illusionPositions.end();
}
