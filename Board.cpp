#include "Board.h"
//modificare constr
Board::Board(int boardSize)
    : size(boardSize), grid(boardSize, std::vector<card>(boardSize, { 0, 0 })), firstCardPlaced(false) {
}

void Board::reset() {
    grid.assign(size, std::vector<card>(size, { 0, 0 }));
    //eliminare
    firstCardPlaced = false;
}
//modificare functie tip si parametrii - ~2 commit uri
PlaceCardResult Board::placeCard(int row, int col, card playCard) {


    if (!(fixedGridRows() && fixedGridColumns()) && isAdjacent(row, col) && shiftGrid(row, col)) {
        std::cout << "The grid has been shifted to accommodate the new position.\n";
    }

    if (row >= 0 && row < size && col >= 0 && col < size) {
        if (isIllusion(row, col)) {
            int illusionCardValue = illusionCards[{row, col}];

            if (playCard.second <= illusionCardValue) {
                std::cout << "Your card is not greater than the illusion. The illusion is now revealed on the board.\n";

                grid[row][col].second = illusionCardValue;

                illusionCards.erase({ row, col });
                illusionPositions.erase(
                    std::remove(illusionPositions.begin(), illusionPositions.end(), std::make_pair(row, col)),
                    illusionPositions.end()
                );

                return PlaceCardResult::CardLost; 
            }
            else {
                grid[row][col] = playCard;
                illusionCards.erase({ row, col });
                illusionPositions.erase(
                    std::remove(illusionPositions.begin(), illusionPositions.end(), std::make_pair(row, col)),
                    illusionPositions.end()
                );
                return PlaceCardResult::Success;
            }
        }

        if (grid[row][col].second != 0) {
            if (playCard.second > grid[row][col].second) {
                grid[row][col] = playCard;
                return PlaceCardResult::Success;
            }
            else {
                std::cout << "You cannot replace a card with a smaller or equal one. Try again.\n";
                return PlaceCardResult::Failure;
            }
        }

        if (firstCardPlaced && !isAdjacent(row, col)) {
            std::cout << "The selected position is not adjacent to an existing card. Try again.\n";
            return PlaceCardResult::Failure;
        }

        grid[row][col] = playCard;
        if (!firstCardPlaced) {
            firstCardPlaced = true;
        }
        return PlaceCardResult::Success;
    }
    return PlaceCardResult::Failure;
}// ~2 commit uri

bool Board::shiftGrid(int& row, int& col) {
    //eliminare juma functie
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
        for (auto& current : grid) {
            current.insert(current.begin(), { 0, 0 });
            current.pop_back();
        }
        col = 0;
    }
    else if (col >= size) {
        for (auto& current : grid) {
            current.push_back({ 0, 0 });
            current.erase(current.begin());
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

//eliminare functie trycovercard

bool Board::isFull() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.second == 0) {
                return false;
            }
        }
    }
    return true;
}
//eliminare revealCard, getsize, getcard

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

bool Board::checkWinCondition(int playerId) const {
    for (int i = 0; i < size; ++i) {
        if (checkRow(i, playerId) || checkColumn(i, playerId)) {
            return true;
        }
    }
    return checkDiagonals(playerId);
}
//modificare display
void Board::display() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.second == 0) {
                std::cout << "[   ] ";
            }
            else if (cell.second == -1) {
                std::cout << "[" << cell.first << ",?] ";
            }
            else {
                std::cout << "[" << cell.first << "," << cell.second << "] ";
            }
        }
        std::cout << "\n";
    }
}//

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
//commit
int Board::calculateCardValueSum(int playerId) const {
    int sum = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.first == playerId) {
                sum += cell.second;
            }
        }
    }
    return sum;
}//commit


//2 commit uri
bool Board::placeIllusion(int row, int col, int playerId, int cardValue) {
    if (!(fixedGridRows() && fixedGridColumns()) && isAdjacent(row, col) && shiftGrid(row, col)) {
        std::cout << "The grid has been shifted to accommodate the new position.\n";
    }

    if (row >= 0 && row < size && col >= 0 && col < size && grid[row][col].second == 0) {

        if (firstCardPlaced && !isAdjacent(row, col)) {
            std::cout << "The selected position is not adjacent to an existing card. Try again.\n";
            return false;
        }

        illusionPositions.push_back({ row, col });
        illusionCards[{row, col}] = cardValue;
        grid[row][col] = { playerId, -1 }; 

        if (!firstCardPlaced) {
            firstCardPlaced = true;
        }
        return true;
    }
    return false;
}//2 commit uri


//commit
bool Board::revealIllusion(int row, int col, int opponentCardValue, int& illusionCardValue) {
    if (illusionCards.count({ row, col }) > 0) {
        illusionCardValue = illusionCards[{row, col}];
        grid[row][col].second = illusionCardValue; 
        return illusionCardValue >= opponentCardValue;
    }
    return false;
}//commit

//adaugare mica
bool Board::isIllusion(int row, int col) const {
    return std::find(illusionPositions.begin(), illusionPositions.end(), std::make_pair(row, col)) != illusionPositions.end();
}//
