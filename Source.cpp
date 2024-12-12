#include "Game.h"
#include <iostream>

int main()
{
    Game game;
    std::cout << "Select Game Mode (1 for Training Mode, 2 for Mage Duel, 3 for Elemental Battle): ";
    int choice;
    std::cin >> choice;
    game.SetGameMode(choice);
    game.StartGame();

    return 0;
}
