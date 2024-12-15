#pragma once
#ifndef EXPLOSIONPATTERN_H
#define EXPLOSIONPATTERN_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
class ExplosionPattern {
private:
	std::vector<std::vector<char>> pattern;
	int size;

public:
	ExplosionPattern(int gridSize);
	void Display() const;
	void Rotate(int degrees);
	std::vector<std::pair<int, int >> GetAffectedPositions() const;
	bool IsHole(int row, int col) const;
	bool IsHand(int row, int col) const;

private:
	std::vector<std::vector< char >> Rotate90(const std::vector<std::vector<char>>& mat);
	void GenerateRandomPattern();

};

#endif

