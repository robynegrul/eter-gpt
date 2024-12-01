#ifndef EXPLOSIONPATTERN_H
#define EXPLOSIONPATTERN_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class ExplosionPattern {
private:
	std::vector<std::vector<char>> pattern;
	int size;

public:
	ExplosionPattern(int gridSize);

	void GenerateRandomPattern();

	void Rotate(int degrees);

	void Display() const;

	std::vector<std::pair<int, int >> GetAffectedPositions() const;

	bool IsHole(int row, int col) const;

	bool IsHand(int row, int col) const;

private:
	std::vector<std::vector< char >> Rotate90(const std::vector<std::vector<char>>& mat);
};

#endif

