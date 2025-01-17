#include "ElementalBattle.h"
ElementalBattle::ElementalBattle() :
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
    explosionExpired{ false },
    turnNumber{ 1 }
{
	InitializePowerDeck();
}

void ElementalBattle::StartGame() {
    while (player1Wins < 2 && player2Wins < 2) {
        ResetRound();
        PlayRound();
    }
    std::cout << "Game Over!\n";
    std::cout << (player1Wins == 2 ? "Player 1 wins the match!\n" : "Player 2 wins the match!\n");
}

void ElementalBattle::ResetRound() {
    activePowers.clear();
    turnNumber = 1; // Resetăm contorul turelor

    if (turnNumber % 2 == 1) {
        ShuffleAndDrawPowers(); // Extragem puteri la începutul rundei impare
    }

    board.Reset();
    player1.ResetCards(3);
    player2.ResetCards(3);

    explosionTriggered = false;
    explosionExpired = false;
    player1UsedIllusion = false;
    player2UsedIllusion = false;

    currentPlayerId = (player1Wins == 0 && player2Wins == 0) ? 1 : (player1Wins > player2Wins ? 1 : 2);
    firstCardPlaced = false;

    std::cout << "NEW ROUND STARTED!\n";
}

void ElementalBattle::PlayRound() {
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

        // Incrementăm turnNumber după fiecare tură
        turnNumber++;

        // Extragem puteri noi la fiecare turnNumber impar
        if (turnNumber % 2 == 1) {
            activePowers.clear();
            if (powerDeck.size() >= 2) {
                activePowers.push_back(powerDeck.back());
                powerDeck.pop_back();
                activePowers.push_back(powerDeck.back());
                powerDeck.pop_back();
            }

            std::cout << "New Elemental Powers for this turn:\n";
            for (size_t i = 0; i < activePowers.size(); ++i) {
                std::cout << i + 1 << ": " << activePowers[i].description << "\n";
            }
        }

        // Schimbăm jucătorul curent
        currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
    }

    DisplayScore();
}

void ElementalBattle::DisplayScore() const {
    std::cout << "Number of victories : \n";
    std::cout << "Player 1: " << player1Wins << "\n";
    std::cout << "Player 2: " << player2Wins << "\n\n";
}

void ElementalBattle::ShowAvailableModes() const {
    std::cout << "Available Game Modes: \n";
    std::cout << "1. Training Mode\n";
}

void ElementalBattle::HandleExplosion(Player& currentPlayer) {
    currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
    Player& explosionPlayer = (currentPlayerId == 1) ? player1 : player2;
	Player& otherPlayer = (currentPlayerId == 1) ? player2 : player1;

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

bool ElementalBattle::HandleCardSelection(Player& currentPlayer) {
    // Afișare puteri disponibile, dacă există
    if (!activePowers.empty()) {
        std::cout << "Available Elemental Powers:\n";
        for (size_t i = 0; i < activePowers.size(); ++i) {
            std::cout << i + 1 << ": " << activePowers[i].description << "\n";
        }

        std::cout << "Player" << currentPlayerId << ", do you want to use an Elemental Power? (y/n): ";
        char usePower;
        std::cin >> usePower;

        if (usePower == 'y' || usePower == 'Y') {
            int powerIndex;
            std::cout << "Select a power (1-" << activePowers.size() << "): ";
            std::cin >> powerIndex;

            // Validare selecție și aplicare putere
            if (powerIndex >= 1 && powerIndex <= static_cast<int>(activePowers.size())) {
                if (UsePower(powerIndex, currentPlayer, (currentPlayerId == 1 ? player2 : player1))) {
                    return true; // Puterea a fost folosită, sfârșim tura
                }
            }
            else {
                std::cout << "Invalid selection. Proceeding to normal card selection.\n";
            }
        }
    }

    // Afișare cărți disponibile și selectare carte
    currentPlayer.DisplayAvailableCards();
    if ((currentPlayerId == 1 && !player1UsedIllusion) || (currentPlayerId == 2 && !player2UsedIllusion)) {
        std::cout << "Player" << currentPlayerId << ", select a card (or enter -1 to use your illusion or 5 to use your ETER card): ";
    }
    else {
        std::cout << "Player" << currentPlayerId << ", select a card: ";
    }

    int cardValue;
    std::cin >> cardValue;

    if (cardValue == -1) {
        HandleIllusion(currentPlayer);
    }
    else {
        return HandleNormalCard(currentPlayer, cardValue);
    }

    return true;
}

void ElementalBattle::HandleIllusion(Player& currentPlayer) {
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

bool ElementalBattle::HandleNormalCard(Player& currentPlayer, int cardValue) {
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

void ElementalBattle::HandleDrawOrWinner() {
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

void ElementalBattle::InitializePowerDeck() {
    powerDeck = {
        { ElementalPowerType::ControlledExplosion, "Trigger an explosion in a selected area." },
        { ElementalPowerType::Destruction, "Destroy an opponent's card on the board." },
        { ElementalPowerType::Flame, "Burn a card and make its cell unusable." },
        { ElementalPowerType::Fire, "Play a fire card that replaces any existing card." },
        { ElementalPowerType::Ash, "Turn an opponent's card into ash, reducing its value to 1." },
        { ElementalPowerType::Spark, "Place an extra card immediately after your turn." },
        { ElementalPowerType::Squall, "Shuffle all cards on the board randomly." },
        { ElementalPowerType::Gale, "Shift all cards in one row or column by one position." },
        { ElementalPowerType::Hurricane, "Blow away all cards in a selected area." },
        { ElementalPowerType::Gust, "Move a card to an adjacent cell." },
        { ElementalPowerType::Mirage, "Create an illusion card that mimics any value." },
        { ElementalPowerType::Storm, "Randomly remove 2 cards from the board." },
        { ElementalPowerType::Tide, "Swap the positions of two cards on the board." },
        { ElementalPowerType::Mist, "Hide a card’s value until the end of the round." },
        { ElementalPowerType::Wave, "Move all cards in one direction until they hit the edge." },
        { ElementalPowerType::Whirlpool, "Remove all cards in a circular area." },
        { ElementalPowerType::Blizzard, "Freeze a row or column, preventing card placement." },
        { ElementalPowerType::Waterfall, "Add a stack of 2 cards to one cell." },
        { ElementalPowerType::Support, "Protect a card from being affected by powers." },
        { ElementalPowerType::Earthquake, "Shake the board, rearranging all cards randomly." },
        { ElementalPowerType::Crumble, "Remove all cards with a value less than 3." },
        { ElementalPowerType::Border, "Create a border around an area to block placement." },
        { ElementalPowerType::Avalanche, "Push all cards in one direction by two cells." },
        { ElementalPowerType::Rock, "Place an indestructible rock card on the board." }
    };

    std::random_device rd;
    std::mt19937 g(rd());  

    std::shuffle(powerDeck.begin(), powerDeck.end(), g);
}

void ElementalBattle::ShuffleAndDrawPowers() {
    if (powerDeck.size() < 2) {
        std::cout << "Not enough Elemental Powers remaining. Game continues without powers.\n";
        return;
    }

    // Resetare puteri și extragere noi
    activePowers.clear();
    if (powerDeck.size() >= 2) {
        activePowers.push_back(powerDeck.back());
        powerDeck.pop_back();
        activePowers.push_back(powerDeck.back());
        powerDeck.pop_back();
    }

    std::cout << "New Elemental Powers for this round:\n";
    for (size_t i = 0; i < activePowers.size(); ++i) {
        std::cout << i + 1 << ": " << activePowers[i].description << "\n";
    }

}

bool ElementalBattle::UsePower(int powerIndex, Player& currentPlayer, Player& opponent) {
    ElementalPower selectedPower = activePowers[powerIndex - 1];
    activePowers.erase(activePowers.begin() + powerIndex - 1);

    switch (selectedPower.type) {
    case ElementalPowerType::ControlledExplosion:
        if (explosionTriggered) {
            std::cout << "A normal explosion has already been triggered. Drawing a new explosion pattern...\n";
            board.DrawAndApplyExplosion(currentPlayer, opponent); // Custom logic for redrawing explosion
        }
        else {
            std::cout << "Triggering a controlled explosion.\n";
            board.ActivateExplosion(currentPlayer, opponent);
            explosionTriggered = true; // Mark explosion as triggered
        }
        break;

    case ElementalPowerType::Destruction:
        std::cout << "Select a card to destroy (row, col): ";
		int row, col;
        std::cin >> row >> col;
        board.ActivateMagicPower(MagicPower::RemoveOpponentCard, row, col, currentPlayer.GetId());
        break;

    case ElementalPowerType::Flame:
        std::cout << "Flaming effect triggered.\n";
        // Implement logic for Flame
        break;

        // Adaugă cazuri pentru fiecare putere

    default:
        std::cout << "Power not implemented yet.\n";
        return false;
    }

    return true;
}
