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

    void generateRandomPattern();

    void rotate(int degrees);

    void display() const;

    std::vector<std::pair<int, int>> getAffectedPositions() const;

    bool isHole(int row, int col) const;

    bool isHand(int row, int col) const;

private:
    std::vector<std::vector<char>> rotate90(const std::vector<std::vector<char>>& mat);
};

#endif
//commit crearea de header plus constructor in cpp - paul
