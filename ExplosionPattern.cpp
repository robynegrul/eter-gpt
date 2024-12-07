#include "ExplosionPattern.h"

ExplosionPattern::ExplosionPattern(int gridSize) : size(gridSize) {
    pattern = std::vector<std::vector<char>>(size, std::vector<char>(size, ' '));
    GenerateRandomPattern();
}

void ExplosionPattern::GenerateRandomPattern() {
    int maxEffects;
    if (size == 3) {
        maxEffects = rand() % 3 + 2;
    }
    else {
        maxEffects = rand() % 4 + 3;
    }

    int starEffects = rand() % 3 + (maxEffects - 2);
    starEffects = std::max(2, starEffects);
    int addedEffects = 0;

    while (addedEffects < starEffects) {
        int row = rand() % size;
        int col = rand() % size;

        if (pattern[row][col] != ' ') {
            continue;
        }
        pattern[row][col] = '*';
        addedEffects++;
    }

    if (addedEffects < maxEffects && rand() % 10 == 0) {
        int holeRow, holeCol;
        do {
            holeRow = rand() % size;
            holeCol = rand() % size;
        } while (pattern[holeRow][holeCol] != ' ');
        pattern[holeRow][holeCol] = 'O';
        addedEffects++;
    }

    if (addedEffects < maxEffects && rand() % 6 == 0) {
        int handRow, handCol;
        do {
            handRow = rand() % size;
            handCol = rand() % size;
        } while (pattern[handRow][handCol] != ' ');
        pattern[handRow][handCol] = 'H';
        addedEffects++;
    }
}

void ExplosionPattern::Rotate(int degrees) {
    int rotations = (degrees / 90) % 4;
    for (int i = 0; i < rotations; ++i)
    {
        pattern = Rotate90(pattern);
    }
}

void ExplosionPattern::Display() const {
    for (const auto& row : pattern) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::pair<int, int>> ExplosionPattern::GetAffectedPositions() const
{
    std::vector<std::pair<int, int>> affectedPositions;
    int center = size / 2;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (pattern[i][j] != ' ') {
                affectedPositions.push_back({ i - center,j - center });
            }
        }
    }
    return affectedPositions;
}

bool ExplosionPattern::IsHole(int row, int col)const {
    return pattern[row][col] == 'O';
}

std::vector<std::vector<char>> ExplosionPattern::Rotate90(const std::vector<std::vector<char>>& mat)
{
    std::vector<std::vector<char>> rotated(size, std::vector<char>(size, ' '));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            rotated[j][size - 1 - i] = mat[i][j];
        }
    }
    return rotated;
}

bool ExplosionPattern::IsHand(int row, int col)const {
    return pattern[row][col] == 'H';
}