#pragma once
#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <string>

class GameMode {
public:
    virtual ~GameMode() = default;
    virtual void start() = 0;
    virtual std::string getName() const = 0;
};

#endif
