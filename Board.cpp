#include "Board.h"
#include "ExplosionPattern.h"
#include <cstdlib>
#include <ctime>
//modifcare constructor
Board::Board(int boardSize)
    : size(boardSize), grid(boardSize, std::vector<card>(boardSize, { 0, 0 })), firstCardPlaced(false) {
}

void Board::reset() {
    grid.assign(size, std::vector<card>(size, { 0, 0 }));
    //eliminare
    firstCardPlaced = false;
}

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
                    illusionPositions.end());
                return PlaceCardResult::CardLost;
            }
            else {
                grid[row][col] = playCard;
                illusionCards.erase({ row, col });
                illusionPositions.erase(
                    std::remove(illusionPositions.begin(), illusionPositions.end(), std::make_pair(row, col)),
                    illusionPositions.end());
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
    //eliminare juma functie ce a ramas
}

//eliminare 2 functii

//modificare functie
bool Board::fixedGridRows() const {
    for (const auto& row : grid) {
        if (std::all_of(row.begin(), row.end(), [](const card& c) { return c.second == 0; })) {
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

//eliminare functie

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
//eliminare 3 functii
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

Explosion Board::generateExplosionEffects(int explosionRow, int rotation) {
    Explosion explosion;

    int effectCount;
    if (size == 3) {
        effectCount = rand() % 3 + 2; // 2 până la 4 efecte
    }
    else {
        effectCount = rand() % 4 + 3; // Altă dimensiune
    }

    for (int i = 0; i < effectCount; ++i) {
        int rowOffset = rand() % size - size / 2;
        int colOffset = rand() % size - size / 2;

        if (explosionRow + rowOffset >= 0 && explosionRow + rowOffset < size &&
            explosionRow + colOffset >= 0 && explosionRow + colOffset < size) {
            explosion.affectedPositions.push_back({ explosionRow + rowOffset, explosionRow + colOffset });
            explosion.effects.push_back((rand() % 10 == 0) ? ExplosionEffect::CreateHole : ExplosionEffect::RemoveCard);
        }
    }

    if (rotation != -1) {
        for (auto& pos : explosion.affectedPositions) {
            int temp = pos.first;
            pos.first = pos.second;
            pos.second = temp;
        }
    }

    return explosion;
}

void Board::applyExplosionEffects(const Explosion& explosion) {
    for (size_t i = 0; i < explosion.affectedPositions.size(); ++i) {
        const auto& [row, col] = explosion.affectedPositions[i];
        if (row < 0 || row >= size || col < 0 || col >= size) continue;

        switch (explosion.effects[i]) {
        case ExplosionEffect::RemoveCard:
            grid[row][col] = { 0, 0 };
            break;
        case ExplosionEffect::CreateHole:
            grid[row][col] = { -1, -1 };
            break;
        }
    }
}

void Board::display() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.second == 0) {
                std::cout << "[   ] "; // Empty cell
            }
            else if (cell.second == -1 && cell.first == -1) {
                std::cout << "[ O ] "; // Hole
            }
            else if (cell.second == -1) {
                std::cout << "[" << cell.first << ",?] "; // Illusion
            }
            else {
                std::cout << "[" << cell.first << "," << cell.second << "] ";
            }
        }
        std::cout << "\n";
    }
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
    }
    return mainDiagonal || secondaryDiagonal;
}

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
}

void Board::activateExplosion(int playerId, Player& player1, Player& player2) {
    if (!canActivateExplosion(playerId)) return;

    srand(time(0));
    ExplosionPattern explosion(3); // Creare grilă explozie 3x3

    // Afișează modelul inițial (0 grade)
    std::cout << "Generated explosion pattern at 0 degrees:\n";
    explosion.display();

    // Stochează modelul inițial pentru referință
    ExplosionPattern initialExplosion = explosion;

    // Previzualizare rotații (90, 180, 270 grade)
    for (int rotation : {90, 180, 270}) {
        explosion = initialExplosion; // Resetare la modelul inițial
        explosion.rotate(rotation);  // Aplică rotația curentă
        std::cout << "Explosion pattern at " << rotation << " degrees:\n";
        explosion.display();
    }

    // Permite jucătorului să aleagă rotația
    int chosenRotation = -1;
    while (chosenRotation != 0 && chosenRotation != 90 && chosenRotation != 180 && chosenRotation != 270) {
        std::cout << "Choose rotation (0, 90, 180, 270): ";
        std::cin >> chosenRotation;
    }

    // Aplică rotația aleasă
    explosion = initialExplosion;
    if (chosenRotation > 0) {
        explosion.rotate(chosenRotation);
    }

    // Automată centrăm explozia pe ultima carte plasată
    int centerRow, centerCol;
    findLastPlacedCard(playerId, centerRow, centerCol);

    // Aplicăm efectele exploziei
    for (const auto& [rowOffset, colOffset] : explosion.getAffectedPositions()) {
        int affectedRow = centerRow + rowOffset;
        int affectedCol = centerCol + colOffset;

        if (affectedRow >= 0 && affectedRow < size && affectedCol >= 0 && affectedCol < size) {
            if (explosion.isHole(rowOffset + 1, colOffset + 1)) {
                grid[affectedRow][affectedCol] = { -1, -1 }; // Marchează ca gaură
            }
            else {
                grid[affectedRow][affectedCol] = { 0, 0 }; // Elimină cartea
            }
        }
    }

    display(); // Afișează tabla actualizată
}

bool Board::canActivateExplosion(int playerId) const {
    int filledRows = 0, filledCols = 0;

    for (int i = 0; i < size; ++i) {
        if (std::all_of(grid[i].begin(), grid[i].end(), [](const card& c) { return c.second != 0; })) {
            filledRows++;
        }
    }

    for (int col = 0; col < size; ++col) {
        bool columnFilled = true;
        for (int row = 0; row < size; ++row) {
            if (grid[row][col].second == 0) {
                columnFilled = false;
                break;
            }
        }
        if (columnFilled) {
            filledCols++;
        }
    }

    return (filledRows >= 2) || (filledCols >= 2) || (filledRows >= 1 && filledCols >= 1);
}

void Board::findLastPlacedCard(int playerId, int& row, int& col) const {
    for (int i = size - 1; i >= 0; --i) {
        for (int j = size - 1; j >= 0; --j) {
            if (grid[i][j].first == playerId) {
                row = i;
                col = j;
                return;
            }
        }
    }
    row = -1;
    col = -1;
}

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
}

bool Board::isIllusion(int row, int col) const {
    return std::find(illusionPositions.begin(), illusionPositions.end(), std::make_pair(row, col)) != illusionPositions.end();
}
