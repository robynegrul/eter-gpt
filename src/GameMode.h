#pragma once

#include <string>

class GameMode {
public:
    virtual ~GameMode() = default;
    virtual void start() = 0;
    virtual std::string getName() const = 0;
};
