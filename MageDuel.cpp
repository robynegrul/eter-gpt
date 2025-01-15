#include "MageDuel.h"

MageDuel::MageDuel() :
	board{ 4 },
	player1{ 1 },
	player2{ 2 },
	player1Wins{ 0 },
	player2Wins{ 0 },
	currentPlayerId{ 1 },
	winnerId{ 1 },
	firstCardPlaced{ false },

	player1UsedMagic{ false },
	player2UsedMagic{ false } {
	mageCards = {
	MageCard(MageType::Fire, "Remove Opponent Card", "Remove Line"),
	MageCard(MageType::Earth, "Cover Opponent Card", "Create Pit"),
	MageCard(MageType::Air, "Move Stack", "Extra Eter Card"),
	MageCard(MageType::Water, "Move Opponent Stack", "Shift Row to Edge")
	};
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

	player1UsedMagic = false;
	player2UsedMagic = false;

	std::vector<MageCard> availableCards = mageCards;

	srand(time(0));
	int index = rand() % availableCards.size();
	player1MageCard = availableCards[index];
	availableCards.erase(availableCards.begin() + index); 

	index = rand() % availableCards.size();
	player2MageCard = availableCards[index];

	bool player1Face1Active = (rand() % 2 == 0);
	bool player2Face1Active = (rand() % 2 == 0);

	std::cout << "Player 1 drew a Mage Card: " << MageTypeToString(player1MageCard.type)
		<< " (Active Face: Power " << (player1Face1Active ? player1MageCard.face1Power : player1MageCard.face2Power) << ")\n";

	std::cout << "Player 2 drew a Mage Card: " << MageTypeToString(player2MageCard.type)
		<< " (Active Face: Power " << (player2Face1Active ? player2MageCard.face1Power : player2MageCard.face2Power) << ")\n";

	player1ActivePower = player1Face1Active ? player1MageCard.face1Power : player1MageCard.face2Power;
	player2ActivePower = player2Face1Active ? player2MageCard.face1Power : player2MageCard.face2Power;

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
	Player& otherPlayer = (currentPlayerId == 1) ? player2 : player1;

	std::cout << "Player " << currentPlayerId << ", do you want to activate an explosion? (y/n): ";//pune pauza dupa player la afisare
	char choice;
	std::cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		board.ActivateExplosion(explosionPlayer, otherPlayer);
		explosionTriggered = true;
        currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
	}
	else {
		explosionExpired = true;
	}

	currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
}

bool MageDuel::HandleCardSelection(Player& currentPlayer) {
	currentPlayer.DisplayAvailableCards();

	std::cout << "Player " << currentPlayerId
		<< ", select an action:\n"
		<< "- Enter -1 for Illusion\n"
		<< "- Enter 0 for Magic Power\n"
		<< "- Enter 5 for Eter Card\n"
		<< "- Enter the value of a card to place it on the board: ";

	int choice;
	std::cin >> choice;

	if (choice == -1) {
		HandleIllusion(currentPlayer);
	}
	else if (choice == 0) {
		HandleMagicPower(currentPlayer);
	}
	else {
		return HandleNormalCard(currentPlayer, choice);
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

void MageDuel::HandleMagicPower(Player& currentPlayer) {
	if ((currentPlayerId == 1 && player1UsedMagic) || (currentPlayerId == 2 && player2UsedMagic)) {
		std::cout << "You have already used your magic power this match!\n";
		return;
	}

	MageType mageType = (currentPlayerId == 1) ? player1MageCard.type : player2MageCard.type;
	std::string activePower = (currentPlayerId == 1) ? player1ActivePower : player2ActivePower;

	std::cout << MageTypeToString(mageType) << " Mage active power: " << activePower << "\n";

	bool powerUsedSuccessfully = false;

	switch (mageType) {
	case MageType::Fire:
		powerUsedSuccessfully = HandleFireMagePower(currentPlayer);
		break;
	case MageType::Earth:
		powerUsedSuccessfully = HandleEarthMagePower(currentPlayer);
		break;
	case MageType::Air:
		powerUsedSuccessfully = HandleAirMagePower(currentPlayer);
		break;
	case MageType::Water:
		powerUsedSuccessfully = HandleWaterMagePower(currentPlayer);
		break;
	default:
		std::cout << "Unknown Mage Type!\n";
		break;
	}
	if (powerUsedSuccessfully) {
		if (currentPlayerId == 1) {
			player1UsedMagic = true;
			currentPlayerId = 2;
		}
		else {
			player2UsedMagic = true;
			currentPlayerId = 1;
		}
	}

	board.Display();
}

bool MageDuel::HandleFireMagePower(Player& currentPlayer) {
	std::cout << "Fire Mage active power: " << player1ActivePower << "\n";

	if (player1ActivePower == "Remove Opponent Card") {
		int row, col;
		std::cout << "Enter position (row, col): ";
		std::cin >> row >> col;
		if (board.ActivateMagicPower(MagicPower::RemoveOpponentCard, row, col, currentPlayerId)) {
			return true;
		}
		else {
			std::cout << "Failed to remove opponent card! Try again.\n";
			return false;
		}
	}
	else if (player1ActivePower == "Remove Row or Column") {
		int index;
		char choice;

		std::cout << "Do you want to remove a row or a column? (r/c): ";
		std::cin >> choice;

		if (choice == 'r') {
			std::cout << "Enter row to remove: ";
			std::cin >> index;
			if (board.ActivateMagicPower(MagicPower::RemoveLine, index, -1, currentPlayerId)) {
				std::cout << "Row " << index << " successfully removed!\n";
				return true;
			}
			else {
				std::cout << "Failed to remove the row.\n";
				return false;
			}
		}
		else if (choice == 'c') {
			std::cout << "Enter column to remove: ";
			std::cin >> index;
			if (board.ActivateMagicPower(MagicPower::RemoveLine, -1, index, currentPlayerId)) {
				std::cout << "Column " << index << " successfully removed!\n";
				return true;
			}
			else {
				std::cout << "Failed to remove the column.\n";
				return false;
			}
		}
		else {
			std::cout << "Invalid choice. Power cancelled.\n";
			return false;
		}
	}
	else {
		std::cout << "Invalid active power for Fire Mage.\n";
		return false;
	}
}

bool MageDuel::HandleEarthMagePower(Player& currentPlayer) {
	std::string currentPlayerActivePower = (currentPlayerId == 1) ? player1ActivePower : player2ActivePower;

	std::cout << "Earth Mage active power: " << currentPlayerActivePower << "\n";

	if (currentPlayerActivePower == "Cover Opponent Card") {
		int row, col, weakerCardValue;
		std::cout << "Enter position (row, col) of opponent's card: ";
		std::cin >> row >> col;

		std::cout << "Enter value of your weaker card: ";
		std::cin >> weakerCardValue;

		if (!currentPlayer.HasCard(weakerCardValue)) {
			std::cout << "You don't have a card with the specified value.\n";
			return false;
		}

		if (board.ActivateMagicPower(MagicPower::CoverOpponentCard, row, col, currentPlayerId, { currentPlayerId, weakerCardValue })) {
			currentPlayer.PlayCard(weakerCardValue);
			return true;
		}
		else {
			std::cout << "Failed to cover opponent's card.\n";
			return false;
		}
	}
	else if (currentPlayerActivePower == "Create Pit") {
		int row, col;

		std::cout << "Enter position (row, col) to create a pit: ";
		std::cin >> row >> col;

		if (board.ActivateMagicPower(MagicPower::CreatePit, row, col, currentPlayerId)) {
			return true;
		}
		else {
			std::cout << "Failed to create a pit.\n";
			return false;
		}
	}

	std::cout << "Invalid active power for Earth Mage.\n";
	return false;
}

bool MageDuel::HandleAirMagePower(Player& currentPlayer) {
	std::string currentPlayerActivePower = (currentPlayerId == 1) ? player1ActivePower : player2ActivePower;

	std::cout << "Air Mage active power: " << currentPlayerActivePower << "\n";

	if (currentPlayerActivePower == "Move Stack") {
		int srcRow, srcCol, destRow, destCol;

		std::cout << "Enter source position (row, col) of the stack: ";
		std::cin >> srcRow >> srcCol;

		std::cout << "Enter destination position (row, col): ";
		std::cin >> destRow >> destCol;

		if (board.ActivateMagicPower(MagicPower::MoveStack, srcRow, srcCol, currentPlayerId, { destRow, destCol })) {
			return true;
		}
		else {
			std::cout << "Failed to move the stack.\n";
			return false;
		}
	}
	else if (currentPlayerActivePower == "Gain Eter Card") {
		int row, col;

		std::cout << "Enter position (row, col) to place your Eter card: ";
		std::cin >> row >> col;

		if (board.ActivateMagicPower(MagicPower::ExtraEterCard, row, col, currentPlayerId)) {
			std::cout << "Eter card successfully placed at (" << row << ", " << col << ").\n";
			return true;
		}
		else {
			std::cout << "Failed to place the Eter card.\n";
			return false;
		}
	}

	std::cout << "Invalid active power for Air Mage.\n";
	return false;
}

bool MageDuel::HandleWaterMagePower(Player& currentPlayer) {
	std::string currentPlayerActivePower = (currentPlayerId == 1) ? player1ActivePower : player2ActivePower;

	std::cout << "Water Mage active power: " << currentPlayerActivePower << "\n";

	if (currentPlayerActivePower == "Move Opponent Stack") {
		int srcRow, srcCol, destRow, destCol;

		std::cout << "Enter source position (row, col) of the opponent's stack: ";
		std::cin >> srcRow >> srcCol;

		std::cout << "Enter destination position (row, col): ";
		std::cin >> destRow >> destCol;

		if (board.ActivateMagicPower(MagicPower::MoveOpponentStack, srcRow, srcCol, currentPlayerId, { destRow, destCol })) {
			return true;
		}
		else {
			std::cout << "Failed to move the opponent's stack.\n";
			return false;
		}
	}
	else if (currentPlayerActivePower == "Shift Row to Edge") {
		char choice;
		int index;

		std::cout << "Do you want to move a row or column? (r/c): ";
		std::cin >> choice;

		std::cout << "Enter the index of the row or column to move: ";
		std::cin >> index;

		bool isRow = (choice == 'r');
		if (board.ActivateMagicPower(MagicPower::ShiftRowToEdge, index, isRow ? 1 : 0, currentPlayerId)) {
			std::cout << "Successfully moved " << (isRow ? "row" : "column") << " " << index << " to the opposite edge.\n";
			return true;
		}
		else {
			std::cout << "Failed to move the " << (isRow ? "row" : "column") << ".\n";
			return false;
		}
	}

	std::cout << "Invalid active power for Water Mage.\n";
	return false;
}

std::string MageDuel::MageTypeToString(MageType type) {
	switch (type) {
	case MageType::Fire: return "Fire";
	case MageType::Earth: return "Earth";
	case MageType::Air: return "Air";
	case MageType::Water: return "Water";
	default: return "Unknown";
	}
}