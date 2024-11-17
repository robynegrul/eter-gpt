#include "Game.h"
#include <iostream>

Game::Game() : board{ 3 }, player1{ 1 }, player2{ 2 }, player1Wins{ 0 }, player2Wins{ 0 }, currentPlayerId{ 1 } {}

void Game::playRound() {
    while (true) {
        
        if (board.isFull()) {
            std::cout << "Board is full. Calculating final scores...\n";
            calculateFinalScores();
            break;
        }

        Player& currentPlayer = (currentPlayerId == 1) ? player1 : player2;
        Player& opponent = (currentPlayerId == 1) ? player2 : player1;

        currentPlayer.displayAvailableCards();
       
        
       
        if (currentPlayer.canUseIllusion()) {
            std::cout << "Choose a card or type -1 to use an illusion: ";
        }
        else {
            std::cout << "Choose a card: ";
        }
		
        int cardValue;
        std::cin >> cardValue;
       

        //eliminare if

        bool validMove = false;//adaugare

        //schimbari din else in if - 3 commit uri - vlad

        //
        if (cardValue == -1 && currentPlayer.canUseIllusion()) {
            std::cout << "Choose a card to use as an illusion: ";
            std::cin >> cardValue;
            if (currentPlayer.useIllusion(cardValue)) {
                std::cout << "Choose a position (row and column) to place the illusion (0 to " << board.getSize() - 1 << "): ";
                int row, col;
                std::cin >> row >> col;
                if (board.placeCard(row, col, { currentPlayerId, 1 }, true)) {
                    validMove = true; 
                }
                else {
                    std::cout << "Invalid move. Try again.\n";
                }
            }
            else {
                std::cout << "Invalid card choice or illusion already used.\n";
            }
        }//

        //
        else if (cardValue != -1) {
            card currentCard = { currentPlayerId, cardValue };
            std::cout << "Choose a position (row and column) (0 to " << board.getSize() - 1 << "): ";
            int row, col;
            std::cin >> row >> col;

            if (board.tryCoverCard(row, col, currentCard)) {
                std::cout << "Failed to replace the illusion! Your card is eliminated, and your turn ends.\n";
                currentPlayer.playCard(cardValue); 
                currentPlayerId = (currentPlayerId == 1) ? 2 : 1; 
                validMove = false; 
            }//

            //
            else if (board.placeCard(row, col, currentCard)) {
                if (currentPlayer.playCard(cardValue)) {
                    if (checkWinCondition()) {
                        std::cout << "Player " << currentPlayerId << " wins!\n";
                        (currentPlayerId == 1) ? player1Wins++ : player2Wins++;
                        break;
                    }
                    currentPlayerId = (currentPlayerId == 1) ? 2 : 1; 
                    validMove = true; 
                }
                else {
                    std::cout << "Invalid move. Try again.\n";
                }
            }
            else {
                std::cout << "Invalid move. Try again.\n";
            }
        }
        else {
            std::cout << "Invalid input. Try again.\n";
        }

        if (validMove) {
            board.display();
        }//

    }//3 commit - vlad
}

void Game::start()
{
    while (player1Wins < 2 && player2Wins < 2)
    {
        resetRound();
        playRound();
        displayScore(); //adaugare functie

        if (player1Wins == 2 || player2Wins == 2)//adaugare
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
    //eliminare rand
    std::cout << "START JOC NOU!\n";
}

bool Game::checkWinCondition()
{
    return board.checkWinCondition(currentPlayerId);
}

void Game::displayScore() const
{
    //modificare mesaj
    std::cout << "Numar de victorii: \n";
    std::cout << "Jucator 1: " << player1Wins << "\n";
    std::cout << "Jucator 2: " << player2Wins << "\n\n";
}

void Game::calculateFinalScores()
{
   
    int player1Score = 0;
    int player2Score = 0;

    for (int row = 0; row < board.getSize(); ++row)
    {
        for (int col = 0; col < board.getSize(); ++col)
        {
            card currentCard = board.getCard(row, col);
            if (currentCard.second != 0) 
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
        player1Wins++; 
    }
    else if (player2Score > player1Score)
    {
        std::cout << "Jucatorul 2 castiga runda pe baza punctajului!\n";
        player2Wins++;
    }
    else
    {
        std::cout << "Egalitate pe baza punctajului!\n";
    }
}
