#include "Game.h"
#include <iostream>

Game::Game() : board{ 3 }, player1{ 1 }, player2{ 2 }, player1Wins{ 0 }, player2Wins{ 0 }, currentPlayerId{ 1 }, firstCardPlaced{ false } {}//

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

void Game::resetRound()
{
	board.reset();
	player1.resetCards();
	player2.resetCards();
	currentPlayerId = 1;
	firstCardPlaced = false;//
	std::cout << "START JOC NOU!\n";
}

bool Game::checkWinCondition()
{
	return board.checkWinCondition(currentPlayerId);
}

void Game::displayScore() const
{
	std::cout << "Scor: \nJucator 1: " << player1Wins << "\nJucator 2: " << player2Wins << "\n\n"; //commit
}

void Game::playRound()//commit in jos functie refacuta
{
	while (true)
	{
		//commit - eu
		Player& currentPlayer = (currentPlayerId == 1) ? player1 : player2;
		currentPlayer.displayAvailableCards();
		

		std::cout << "Jucatorul " << currentPlayerId << " alege o carte: ";
		int cardValue;
		std::cin >> cardValue;
		card currentCard = { currentPlayerId,cardValue };

		if (!firstCardPlaced)
		{
			if (board.placeCard(1, 1, currentCard) && currentPlayer.playCard(currentCard.second))
			{
				firstCardPlaced = true;
				currentPlayerId = 2;
				board.display();
			}
		}//commit 
		else//commit in jos remodelare - eu
		{
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
			}
		}//commit
	}
}

