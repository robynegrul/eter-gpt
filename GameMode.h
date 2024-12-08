#pragma once
#ifndef GAMEMODE_H
#define GAMEMODE_H

//eliminare enum, adaugare include

#include <string>

//creare clasa gamemode
class GameMode {
public:
    virtual ~GameMode() = default;
    virtual void start() = 0;
    virtual std::string getName() const = 0;
};

#endif
