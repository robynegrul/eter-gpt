#include "ExplosionPattern.h"

ExplosionPattern::ExplosionPattern(int gridSize) : size(gridSize) {
	pattern = std::vector<std::vector<char>>(size, std::vector<char>(size, ' '));
	GenerateRandomPattern();
}

void ExplosionPattern::GenerateRandomPattern() {
	int maxEffects = (size == 3) ? rand() % 3 + 2 : rand() % 4 + 3;
	int addedEffects = 0;

	while (addedEffects < maxEffects) {
		int row, col;
		do {
			row = rand() % size;
			col = rand() % size;
		} while (pattern[row][col] != ' ');

		int effectChance = rand() % 100;

		if (effectChance < 50) {
			pattern[row][col] = '*';
		}
		else if (effectChance < 90) {
			pattern[row][col] = 'H';
		}
		else {
			pattern[row][col] = 'O';
		}

		++addedEffects;
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
