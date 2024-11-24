#include "Game.h"
#include <iostream>

Game::Game()
    : board(3), player1(1), player2(2), player1Wins(0), player2Wins(0), currentPlayerId(1),
    firstCardPlaced(false), player1UsedIllusion(false), player2UsedIllusion(false), explosionTriggered(false) {
}

void Game::start() {
    while (player1Wins < 2 && player2Wins < 2) {
        resetRound();
        playRound();
    }
    std::cout << "Game Over!\n";
    std::cout << (player1Wins == 2 ? "Player 1 wins the match!\n" : "Player 2 wins the match!\n");
}

void Game::resetRound() {
    board.reset();
    player1.resetCards();
    player2.resetCards();

    explosionTriggered = false;

    player1UsedIllusion = false;
    player2UsedIllusion = false;

    if (player1Wins == 0 && player2Wins == 0) {
        currentPlayerId = 1;
    }
    else if (player1Wins > player2Wins) {
        currentPlayerId = 1;
    }
    else {
        currentPlayerId = 2;
    }

    firstCardPlaced = false;

    std::cout << "NEW ROUND STARTED!\n";
}

void Game::playRound() {
    while (true) {
        Player& currentPlayer = (currentPlayerId == 1) ? player1 : player2;

        currentPlayer.displayAvailableCards();

        if (board.canActivateExplosion(currentPlayerId) && !explosionTriggered) {
            std::cout << "Player " << currentPlayerId << ", do you want to activate an explosion? (y/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                board.activateExplosion(currentPlayerId, player1, player2);
                explosionTriggered = true;
                continue;
            }
        }

        if ((currentPlayerId == 1 && !player1UsedIllusion) || (currentPlayerId == 2 && !player2UsedIllusion)) {
            std::cout << "Player " << currentPlayerId << ", select a card (or enter -1 to use your illusion): ";
        }
        else {
            std::cout << "Player " << currentPlayerId << ", select a card: ";
        }

        int cardValue;
        std::cin >> cardValue;

        if (cardValue == -1) {
            if ((currentPlayerId == 1 && player1UsedIllusion) || (currentPlayerId == 2 && player2UsedIllusion)) {
                std::cout << "You have already used your illusion this round!\n";
                continue;
            }

            std::cout << "Select a card from your hand to use as the illusion: ";
            int illusionCardValue;
            std::cin >> illusionCardValue;

            if (!currentPlayer.hasCard(illusionCardValue)) {
                std::cout << "Invalid card selection. Try again.\n";
                continue;
            }

            std::cout << "Choose position (row and column) for your illusion: ";
            int row, col;
            std::cin >> row >> col;

            if (board.placeIllusion(row, col, currentPlayerId, illusionCardValue)) {
                currentPlayer.playCard(illusionCardValue);
                if (currentPlayerId == 1) player1UsedIllusion = true;
                else player2UsedIllusion = true;

                std::cout << "Illusion placed successfully.\n";
                currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
                board.display();
            }
            else {
                std::cout << "The selected position is not valid. Try again.\n";
            }
        }
        else {
            card currentCard = { currentPlayerId, cardValue };

            if (!currentPlayer.hasCard(cardValue)) {
                std::cout << "Invalid card selection. Try again.\n";
                continue;
            }

            std::cout << "Choose position (row and column): ";
            int row, col;
            std::cin >> row >> col;

            PlaceCardResult result = board.placeCard(row, col, currentCard);
            if (result == PlaceCardResult::CardLost) {
                std::cout << "Your card has been lost due to the illusion.\n";
                currentPlayer.playCard(cardValue);
                currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
            }
            else if (result == PlaceCardResult::Failure) {
                std::cout << "Invalid position. Try again.\n";
            }
            else if (result == PlaceCardResult::Success) {
                if (currentPlayer.playCard(cardValue)) {
                    board.display();

                    if (board.checkWinCondition(currentPlayerId)) {
                        std::cout << "Player " << currentPlayerId << " wins!\n\n";
                        if (currentPlayerId == 1) player1Wins++;
                        else player2Wins++;
                        break;
                    }

                    if (board.isFull()) {
                        int player1Sum = board.calculateCardValueSum(1);
                        int player2Sum = board.calculateCardValueSum(2);

                        std::cout << "The board is full!\n";
                        std::cout << "Player 1's total card sum: " << player1Sum << "\n";
                        std::cout << "Player 2's total card sum: " << player2Sum << "\n";

                        if (player1Sum > player2Sum) {
                            std::cout << "Player 1 wins the round with a higher card sum!\n";
                            player1Wins++;
                        }
                        else if (player2Sum > player1Sum) {
                            std::cout << "Player 2 wins the round with a higher card sum!\n";
                            player2Wins++;
                        }
                        else {
                            std::cout << "It's a draw! Both players have the same card sum.\n";
                        }
                        break;
                    }

                    currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
                }
            }
        }
    }
}

void Game::displayScore() const {
    std::cout << "Score: \nPlayer 1: " << player1Wins << "\nPlayer 2: " << player2Wins << "\n\n";
}
