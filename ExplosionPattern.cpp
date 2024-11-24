#include "ExplosionPattern.h"

ExplosionPattern::ExplosionPattern(int gridSize) : size(gridSize) {
    pattern = std::vector<std::vector<char>>(size, std::vector<char>(size, ' '));
    generateRandomPattern();
}

void ExplosionPattern::generateRandomPattern() {
    int maxEffects;
    if (size == 3) {
        maxEffects = rand() % 3 + 2;
    }
    else {
        maxEffects = rand() % 4 + 3;
    }

    int addedEffects = 0;

    while (addedEffects < maxEffects) {
        int row = rand() % size;
        int col = rand() % size;

        if (pattern[row][col] != ' ') {
            continue;
        }

        pattern[row][col] = '*';
        addedEffects++;
    }

    if (addedEffects < maxEffects && rand() % 2 == 0) {
        int handRow, handCol;
        do {
            handRow = rand() % size;
            handCol = rand() % size;
        } while (pattern[handRow][handCol] != ' ');
        pattern[handRow][handCol] = 'H';
        addedEffects++;
    }

    if (addedEffects < maxEffects && rand() % 2 == 0) {
        int holeRow, holeCol;
        do {
            holeRow = rand() % size;
            holeCol = rand() % size;
        } while (pattern[holeRow][holeCol] != ' ');
        pattern[holeRow][holeCol] = 'O';
        addedEffects++;
    }
}

void ExplosionPattern::rotate(int degrees) {
    int rotations = (degrees / 90) % 4;
    for (int i = 0; i < rotations; ++i) {
        pattern = rotate90(pattern);
    }
}

void ExplosionPattern::display() const {
    for (const auto& row : pattern) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::pair<int, int>> ExplosionPattern::getAffectedPositions() const {
    std::vector<std::pair<int, int>> affectedPositions;
    int center = size / 2;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (pattern[i][j] != ' ') {
                affectedPositions.push_back({ i - center, j - center });
            }
        }
    }
    return affectedPositions;
}

std::vector<std::vector<char>> ExplosionPattern::rotate90(const std::vector<std::vector<char>>& mat) {
    std::vector<std::vector<char>> rotated(size, std::vector<char>(size, ' '));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            rotated[j][size - 1 - i] = mat[i][j];
        }
    }
    return rotated;
}

bool ExplosionPattern::isHole(int row, int col) const {
    return pattern[row][col] == 'O';
}

bool ExplosionPattern::isHand(int row, int col) const {
    return pattern[row][col] == 'H';
}
