#include "Board.h"
#include "Player.h"
#include <iostream>

int main() {
    int boardSize = 3;
    Board board(boardSize);
    Player player1(1);
    Player player2(2);
	int player1Wins = 0;
	int player2Wins = 0;
    int currentPlayerId = 1;

    while (player1Wins < 2 && player2Wins < 2)
    {
        std::cout << "START JOC NOU!\n";
        board.reset();
        player1.resetCards();
        player2.resetCards();

        while (true) {
            board.display();
            std::cout << "Jucatorul " << currentPlayerId << " alege o carte (1-4): ";
            int cardValue;
            std::cin >> cardValue;

            std::cout << "Alege pozitia (rand si coloana): ";
            int row, col;
            std::cin >> row >> col;

            Player& currentPlayer = (currentPlayerId == 1) ? player1 : player2;

            if (currentPlayer.playCard(cardValue) && board.placeCard(row, col, currentPlayerId)) {
                if (board.checkWinCondition(currentPlayerId)) {
                    board.display();
                    std::cout << "Jucatorul " << currentPlayerId << " a castigat!\n";
                    if (currentPlayerId == 1)
                    {
                        player1Wins++;
                        std::cout << "Jucatorul " << currentPlayerId << " are " << player1Wins<< "/2\n";

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
            else {
                std::cout << "Mutare invalida, incearca din nou.\n";
            }
            std::cout << "Scor: Jucator 1: " << player1Wins << " Jucator 2: " << player2Wins << "\n";
        }
    }

    std::cout << "Meci incheiat!\n";
    std::cout << (player1Wins == 2 ? "Jucatorul 1 a castigat meciul!\n" : "Jucatorul 2 a castigat meciul!\n");
    return 0;
}
