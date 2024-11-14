#include "Game.h"
#include <iostream>

Game::Game() : board{ 3 }, player1{ 1 }, player2{ 2 }, player1Wins{ 0 }, player2Wins{ 0 }, currentPlayerId{ 1 }, firstCardPlaced{ false } {}

void Game::start()
{
    while (player1Wins < 2 && player2Wins < 2)
    {
        resetRound();
        playRound();
        displayScore(); // Display number of victories at the end of each round

        // Check if any player has reached 2 victories and end the match
        if (player1Wins == 2 || player2Wins == 2)
            break;
    }
    std::cout << "Meci incheiat!\n";
    std::cout << (player1Wins == 2 ? "Jucatorul 1 a castigat meciul!\n" : "Jucatorul 2 a castigat meciul!\n");
}

void Game::resetRound()
{
    board.reset();
    player1.resetCards();
    player2.resetCards();
    currentPlayerId = 1;
    firstCardPlaced = false;
    std::cout << "START JOC NOU!\n";
}

bool Game::checkWinCondition()
{
    return board.checkWinCondition(currentPlayerId);
}

void Game::displayScore() const
{
    std::cout << "Numar de victorii: \n";
    std::cout << "Jucator 1: " << player1Wins << "\n";
    std::cout << "Jucator 2: " << player2Wins << "\n\n";
}

void Game::playRound()
{
    while (true)
    {
        // Check if both players have no cards left or if the board is full
        if ((!player1.hasCardsLeft() && !player2.hasCardsLeft()) || board.isFull())
        {
            std::cout << "Egalitate! Nu mai sunt carti disponibile sau tabla este plina.\n";
            calculateFinalScores(); // Calculate points from cards only when the board is full or cards are exhausted
            break;
        }

        Player& currentPlayer = (currentPlayerId == 1) ? player1 : player2;
        currentPlayer.displayAvailableCards();

        std::cout << "Jucatorul " << currentPlayerId << " alege o carte: ";
        int cardValue;
        std::cin >> cardValue;
        card currentCard = { currentPlayerId, cardValue };

        std::cout << "Alege pozitia (rand si coloana): ";
        int row, col;
        std::cin >> row >> col;

        if (board.placeCard(row, col, currentCard))
        {
            board.display();
            if (currentPlayer.playCard(cardValue))
            {
                if (checkWinCondition())
                {
                    std::cout << "Jucatorul " << currentPlayerId << " a castigat!\n\n";
                    if (currentPlayerId == 1)
                    {
                        player1Wins++;
                    }
                    else
                    {
                        player2Wins++;
                    }
                    break;
                }
                currentPlayerId = (currentPlayerId == 1) ? 2 : 1; // Switch players
            }
            else
            {
                std::cout << "Mutare invalida, incearca din nou.\n";
            }
        }
    }
}

void Game::calculateFinalScores()
{
    int player1Score = 0;
    int player2Score = 0;

    // Loop through the board to sum visible card values
    for (int row = 0; row < board.getSize(); ++row)
    {
        for (int col = 0; col < board.getSize(); ++col)
        {
            card currentCard = board.getCard(row, col);
            if (currentCard.second != 0) // Card is visible
            {
                if (currentCard.first == 1)
                    player1Score += currentCard.second;
                else if (currentCard.first == 2)
                    player2Score += currentCard.second;
            }
        }
    }

    std::cout << "Punctajul cartilor: \n";
    std::cout << "Jucator 1: " << player1Score << "\n";
    std::cout << "Jucator 2: " << player2Score << "\n";
    if (player1Score > player2Score)
    {
        std::cout << "Jucatorul 1 castiga runda pe baza punctajului!\n";
        player1Wins++; // Update the victory count
    }
    else if (player2Score > player1Score)
    {
        std::cout << "Jucatorul 2 castiga runda pe baza punctajului!\n";
        player2Wins++; // Update the victory count
    }
    else
    {
        std::cout << "Egalitate pe baza punctajului!\n";
    }
}
