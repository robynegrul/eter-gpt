#include "MageDuel.h"
//elimina iostream
MageDuel::MageDuel() :
    board{ 4 },
    player1{ 1 },
    player2{ 2 },
    player1Wins{ 0 },
    player2Wins{ 0 },
    currentPlayerId{ 1 },
    winnerId{ 1 },
    firstCardPlaced{ false },
    player1UsedIllusion{ false },
    player2UsedIllusion{ false },
    explosionTriggered{ false },
    explosionExpired{ false }
{
}

void MageDuel::StartGame() {
    while (player1Wins < 2 && player2Wins < 2) {
        ResetRound();
        PlayRound();
    }
    std::cout << "Game Over!\n";
    std::cout << (player1Wins == 2 ? "Player 1 wins the match!\n" : "Player 2 wins the match!\n");
}

void MageDuel::ResetRound() {
    board.Reset();
    player1.ResetCards(2);
    player2.ResetCards(2);

    explosionTriggered = false;
    explosionExpired = false;
    player1UsedIllusion = false;
    player2UsedIllusion = false;

    currentPlayerId = (player1Wins == 0 && player2Wins == 0) ? 1 : (player1Wins > player2Wins ? 1 : 2);
    firstCardPlaced = false;

    std::cout << "NEW ROUND STARTED!\n";
}

void MageDuel::PlayRound() {
    currentPlayerId = winnerId;
    while (true) {
        Player& currentPlayer = (currentPlayerId == 1) ? player1 : player2;

        if (board.CanActivateExplosion() && !explosionTriggered && !explosionExpired) {
            HandleExplosion(currentPlayer);
        }
        else {
            if (!HandleCardSelection(currentPlayer)) {
                break;
            }
        }
    }

    DisplayScore();
}

void MageDuel::DisplayScore() const {
    std::cout << "Number of victories : \n";
    std::cout << "Player 1: " << player1Wins << "\n";
    std::cout << "Player 2: " << player2Wins << "\n\n";
}

void MageDuel::ShowAvailableModes() const {
    std::cout << "Available Game Modes: \n";
    std::cout << "1. Training Mode\n";
}

void MageDuel::HandleExplosion(Player& currentPlayer) {
    currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
    Player& explosionPlayer = (currentPlayerId == 1) ? player1 : player2;
    Player& otherPlayer = (currentPlayerId == 1) ? player2 : player1;//adauga

    std::cout << "Player" << currentPlayerId << ", do you want to activate an explosion? (y/n): ";
    char choice;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        board.ActivateExplosion(explosionPlayer, otherPlayer);
        explosionTriggered = true;
        currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
    }
    else {
        explosionExpired = true;
        currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
    }
}

bool MageDuel::HandleCardSelection(Player& currentPlayer) {
    currentPlayer.DisplayAvailableCards();
    if ((currentPlayerId == 1 && !player1UsedIllusion) || (currentPlayerId == 2 && !player2UsedIllusion))
    {
        std::cout << "Player" << currentPlayerId << ", select a card (or enter -1 to use your illusion or 5 to use your ETER card): ";
    }
    else
    {
        std::cout << "Player" << currentPlayerId << ", select a card: ";
    }

    int cardValue;
    std::cin >> cardValue;

    if (cardValue == -1) {
        HandleIllusion(currentPlayer);
    }
    else {
        return(HandleNormalCard(currentPlayer, cardValue));
    }
    return true;
}

void MageDuel::HandleIllusion(Player& currentPlayer) {
    if ((currentPlayerId == 1 && player1UsedIllusion) || (currentPlayerId == 2 && player2UsedIllusion)) {
        std::cout << "You have already used your illusion this round!\n";
        return;
    }

    std::cout << "Select a card from your hand to use as the illusion: ";
    int illusionCardValue;
    std::cin >> illusionCardValue;

    if (!currentPlayer.HasCard(illusionCardValue)) {
        std::cout << "Invalid card selection. Try again.\n";
        return;
    }
    
    std::cout << "Choose position (row and column) for your illusion: ";
    int row, col;
    std::cin >> row >> col;

    if (board.PlaceIllusion(row, col, currentPlayerId, illusionCardValue)) {
        currentPlayer.PlayCard(illusionCardValue);
        if (currentPlayerId == 1) player1UsedIllusion = true;
        else player2UsedIllusion = true;

        std::cout << "Illusion placed successfully.\n";
        currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
        board.Display();
    }
    else {
        std::cout << "The selected position is not valid. Try again.\n";
    }
}

bool MageDuel::HandleNormalCard(Player& currentPlayer, int cardValue) {
    card currentCard = { currentPlayerId, cardValue };

    if (!currentPlayer.HasCard(cardValue)) {
        std::cout << "Invalid card selection. Try again.\n";
        return true;
    }

    std::cout << "Choose position (row and column): ";
    int row, col;
    std::cin >> row >> col;

    PlaceCardResult result = board.PlaceCard(row, col, currentCard);
    if (result == PlaceCardResult::CardLost) {
        std::cout << "Your card has been lost due to the illusion.\n";
        currentPlayer.PlayCard(cardValue);
        currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
        board.Display();
    }
    else if (result == PlaceCardResult::Failure) {
        std::cout << "Invalid position. Try again.\n";
    }
    else if (result == PlaceCardResult::Success) {
        if (currentPlayer.PlayCard(cardValue)) {
            board.Display();

            if (board.CheckWinCondition(currentPlayerId)) {
                std::cout << "Player" << currentPlayerId << " wins!\n";
                if (currentPlayerId == 1) {
                    player1Wins++;
                    winnerId = 1;
                }
                else {
                    player2Wins++;
                    winnerId = 2;
                }
                return false;
            }

            if (board.IsFull()) {
                HandleDrawOrWinner();
                return false;
            }
            currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
        }
    }

    return true;
}

void MageDuel::HandleDrawOrWinner() {
    int player1Sum = board.CalculateCardValueSum(1);
    int player2Sum = board.CalculateCardValueSum(2);

    std::cout << "The board is full!\n";
    std::cout << "Player 1's total card sum: " << player1Sum << "\n";
    std::cout << "Player 2's total card sum: " << player2Sum << "\n";

    if (player1Sum > player2Sum) {
        std::cout << "Player 1 wins the round with a higher card sum!\n";
        player1Wins++;
        winnerId = 1;
    }
    else if (player1Sum < player2Sum) {
        std::cout << "Player 2 wins the round with a higher card sum!\n";
        player2Wins++;
        winnerId = 2;
    }
    else {
        std::cout << "It's a draw! Both players have the same card sum.\n";
    }
}