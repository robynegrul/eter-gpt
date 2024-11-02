#include "Game.h"
#include <iostream>

Game::Game() : board(3), player1(1), player2(2), player1Wins(0), player2Wins(0), currentPlayerId(1) {}

void Game::start() 
{
    while (player1Wins < 2 && player2Wins < 2) 
    {
        resetRound();
        playRound();
    }
    std::cout << "Meci incheiat!\n";
    std::cout << (player1Wins == 2 ? "Jucatorul 1 a castigat meciul!\n" : "Jucatorul 2 a castigat meciul!\n");
}

void Game::playRound() 
{
    while (true) 
    {
        board.display();
        std::cout << "Jucatorul " << currentPlayerId << " alege o carte (1-4): ";
        int cardValue;
        std::cin >> cardValue;

        std::cout << "Alege pozitia (rand si coloana): ";
        int row, col;
        std::cin >> row >> col;

        Player& currentPlayer = (currentPlayerId == 1) ? player1 : player2;

        if (currentPlayer.playCard(cardValue) && board.placeCard(row, col, currentPlayerId))
        {
            if (checkWinCondition()) 
            {
                board.display();
                std::cout << "Jucatorul " << currentPlayerId << " a castigat!\n";
                if (currentPlayerId == 1) 
                {
                    player1Wins++;
                    std::cout << "Jucatorul " << currentPlayerId << " are " << player1Wins << "/2\n";
                }
                else 
                {
                    player2Wins++;
                    std::cout << "Jucatorul " << currentPlayerId << " are " << player2Wins << "/2\n";
                }
                break;
            }
            if (!player1.hasCardsLeft() && !player2.hasCardsLeft()) 
            {
                std::cout << "Egalitate! Nu mai sunt carti disponibile.\n";
                break;
            }
            currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
        }
        else 
        {
            std::cout << "Mutare invalida, incearca din nou.\n";
        }
        displayScore();
    }
}

void Game::resetRound() 
{
    board.reset();
    player1.resetCards();
    player2.resetCards();
    currentPlayerId = 1;
    std::cout << "START JOC NOU!\n";
}

bool Game::checkWinCondition() 
{
    return board.checkWinCondition(currentPlayerId);
}

void Game::displayScore() const 
{
    std::cout << "Scor: Jucator 1: " << player1Wins << " Jucator 2: " << player2Wins << "\n";
}
