#include "Board.h"

Board::Board(int boardSize)
	: size{ boardSize }, grid(boardSize, std::vector<std::optional<std::stack<card>>>(boardSize, std::nullopt)), firstCardPlaced{ false } {
}

void Board::Reset()
{
	EliminateIllusions();
	grid.assign(size, std::vector<std::optional<std::stack<card>>>(size, std::nullopt));
	firstCardPlaced = false;
}

PlaceCardResult Board::PlaceCard(int row, int col, card playCard) {
	if (IsAdjacent(row, col) && ShiftGrid(row, col)) {
		std::cout << "The grid has been shifted.\n";
	}

	if (row >= 0 && row < size && col >= 0 && col < size) {
		if (IsIllusion(row, col)) {
			int illusionCardValue = illusionCards[{row, col}];

			if (playCard.second <= illusionCardValue) {
				std::cout << "Your card is not greater than the illusion. The illusion is now revealed on the board.\n";
				grid[row][col]->top().second = illusionCardValue;
				EliminateIllusions();
				return PlaceCardResult::CardLost;
			}
			else {
				if (!grid[row][col].has_value()) {
					grid[row][col] = std::make_optional<std::stack<card>>();
				}
				grid[row][col]->push(playCard);
				EliminateIllusions();
				return PlaceCardResult::Success;
			}
		}

		if (playCard.second == 5 && grid[row][col].has_value()) {
			std::cout << "You cannot place the Eter card on a non-empty cell.\n";
			return PlaceCardResult::Failure;
		}

		if (grid[row][col].has_value() && !grid[row][col]->empty() && grid[row][col]->top().second == 5) {
			std::cout << "You cannot replace the Eter card.\n";
			return PlaceCardResult::Failure;
		}

		if (grid[row][col].has_value() && grid[row][col]->empty()) {
			std::cout << "You cannot place a card on a hole.\n";
			return PlaceCardResult::Failure;
		}

		if (grid[row][col].has_value() && !grid[row][col]->empty()) {
			if (playCard.second > grid[row][col]->top().second) {
				grid[row][col]->push(playCard);
				return PlaceCardResult::Success;
			}
			else {
				std::cout << "You cannot replace a card with a lower or equal one. Try again.\n";
				return PlaceCardResult::Failure;
			}
		}

		if (firstCardPlaced && !IsAdjacent(row, col)) {
			std::cout << "The selected position is not adjacent to an existing card. Try again.\n";
			return PlaceCardResult::Failure;
		}

		if (!grid[row][col].has_value()) {
			grid[row][col] = std::make_optional<std::stack<card>>();
		}
		grid[row][col]->push(playCard);

		if (!firstCardPlaced) {
			firstCardPlaced = true;
		}

		return PlaceCardResult::Success;
	}

	return PlaceCardResult::Failure;
}

bool Board::DiagonalShift(int& row, int& col) {
	bool shifted = false;
	if (((row == -1 && col == -1) || (row == size && col == size)) && !FixedGridColumns() && !FixedGridRows()) {
		if (row < 0) {
			grid.insert(grid.begin(), std::vector<std::optional<std::stack<card>>>(size, std::nullopt));
			grid.pop_back();
			row = 0;
			shifted = true;
		}
		else if (row >= size) {
			grid.push_back(std::vector<std::optional<std::stack<card>>>(size, std::nullopt));
			grid.erase(grid.begin());
			row = size - 1;
			shifted = true;
		}

		if (col < 0) {
			for (auto& r : grid) {
				r.insert(r.begin(), std::nullopt);
				r.pop_back();
			}
			col = 0;
			shifted = true;
		}
		else if (col >= size) {
			for (auto& r : grid) {
				r.push_back(std::nullopt);
				r.erase(r.begin());
			}
			col = size - 1;
			shifted = true;
		}
	}
	return shifted;
}

bool Board::VerticalShift(int& row, int& col) {
	bool shifted = false;
	if ((row == -1 || row == size) && !FixedGridRows()) {
		if (row == -1) {
			grid.insert(grid.begin(), std::vector<std::optional<std::stack<card>>>(size, std::nullopt));
			grid.pop_back();
			row = 0;
			shifted = true;
		}
		else if (row == size) {
			grid.push_back(std::vector<std::optional<std::stack<card>>>(size, std::nullopt));
			grid.erase(grid.begin());
			row = size - 1;
			shifted = true;
		}
	}
	return shifted;
}

bool Board::HorizontalShift(int& row, int& col) {
	bool shifted = false;
	if ((col == -1 || col == size) && !FixedGridColumns()) {
		if (col == -1) {
			for (auto& r : grid) {
				r.insert(r.begin(), std::nullopt);
				r.pop_back();
			}
			col = 0;
			shifted = true;
		}
		else if (col == size) {
			for (auto& r : grid) {
				r.push_back(std::nullopt);
				r.erase(r.begin());
			}
			col = size - 1;
			shifted = true;
		}
	}
	return shifted;
}

bool Board::ShiftGrid(int& row, int& col) {
	if ((row == -1 && col == -1) || (row == size && col == size)) {
		return DiagonalShift(row, col);
	}
	else if (row == -1 || row == size) {
		return VerticalShift(row, col);
	}
	else if (col == -1 || col == size) {
		return HorizontalShift(row, col);
	}
	return false;
}

bool Board::FixedGridRows() const {
	for (int row = 0; row < size; ++row) {
		bool hasElement = false;
		for (int col = 0; col < size; ++col) {
			if (grid[row][col].has_value() && !grid[row][col]->empty()) {
				hasElement = true;
				break;
			}
		}
		if (!hasElement) {
			return false;
		}
	}
	return true;
}

bool Board::FixedGridColumns() const {
	for (int col = 0; col < size; ++col) {
		bool hasElement = false;
		for (int row = 0; row < size; ++row) {
			if (grid[row][col].has_value() && !grid[row][col]->empty()) {
				hasElement = true;
				break;
			}
		}
		if (!hasElement) {
			return false;
		}
	}
	return true;
}

bool Board::IsFull() const {
	for (const auto& row : grid) {
		for (const auto& cell : row) {
			if (!cell.has_value() || cell->empty()) {
				return false;
			}
		}
	}
	return true;
}

bool Board::IsAdjacent(int row, int col) const {
	int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (auto& dir : directions) {
		int newRow = row + dir[0];
		int newCol = col + dir[1];
		if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
			if (grid[newRow][newCol].has_value() && !grid[newRow][newCol]->empty()) {
				return true;
			}
		}
	}
	return false;
}

bool Board::CheckWinCondition(int playerId) const
{
	for (int i = 0; i < size; ++i)
	{
		if (CheckRow(i, playerId) || CheckColumn(i, playerId))
			return true;
	}
	return CheckDiagonals(playerId);
}

void Board::Display() const {
	for (const auto& row : grid) {
		for (const auto& cell : row) {
			if (!cell.has_value()) {
				std::cout << "[   ] ";
			}
			else if (cell->empty()) {
				std::cout << "[ O ] ";
			}
			else {
				const card& topCard = cell->top();
				if (topCard.second == -1) {
					std::cout << "[" << topCard.first << ",?] ";
				}
				else if (topCard.second == 5) {
					std::cout << "[" << topCard.first << ",E] ";
				}
				else {
					std::cout << "[" << topCard.first << "," << topCard.second << "] ";
				}
			}
		}
		std::cout << "\n";
	}
}

void Board::ApplyExplosionEffects(const Explosion& explosion, Player& player, Player& other) {
	for (size_t i = 0; i < explosion.affectedPositions.size(); ++i) {
		const auto& [row, col] = explosion.affectedPositions[i];

		switch (explosion.effects[i]) {
		case ExplosionEffect::RemoveCard:
			if (grid[row][col].has_value() && !grid[row][col]->empty()) {
				grid[row][col]->pop();
				if (grid[row][col]->empty()) {
					grid[row][col].reset();  				}
			}
			break;
		case ExplosionEffect::CreateHole:
			grid[row][col] = std::make_optional<std::stack<card>>();
			break;
		case ExplosionEffect::TakeHand:
			if (grid[row][col].has_value() && !grid[row][col]->empty()) {
				card currentCard = grid[row][col]->top();
				grid[row][col]->pop();
				if (grid[row][col]->empty()) {
					grid[row][col].reset();
				}
				if (currentCard.first == player.GetId()) {
					player.AddCard(currentCard.second);
				}
				else {
					other.AddCard(currentCard.second);
				}
			}
			break;
		}
	}
}

bool Board::CheckRow(int row, int playerId) const {
	for (int col = 0; col < size; ++col) {
		if (!grid[row][col].has_value() || grid[row][col]->empty() || grid[row][col]->top().first != playerId) {
			return false;
		}
	}
	return true;
}

bool Board::CheckColumn(int col, int playerId) const {
	for (int row = 0; row < size; ++row) {
		if (!grid[row][col].has_value() || grid[row][col]->empty() || grid[row][col]->top().first != playerId) {
			return false;
		}
	}
	return true;
}

bool Board::CheckDiagonals(int playerId) const {
	bool mainDiagonal = true;
	bool secondaryDiagonal = true;

	for (int i = 0; i < size; ++i) {
		if (!grid[i][i].has_value() || grid[i][i]->empty() || grid[i][i]->top().first != playerId) {
			mainDiagonal = false;
		}

		if (!grid[i][size - i - 1].has_value() || grid[i][size - i - 1]->empty() || grid[i][size - i - 1]->top().first != playerId) {
			secondaryDiagonal = false;
		}

		if (!mainDiagonal && !secondaryDiagonal) {
			return false;
		}
	}

	return mainDiagonal || secondaryDiagonal;
}

bool Board::PlaceIllusion(int row, int col, int playerId, int cardValue) {
	if (!(FixedGridRows() && FixedGridColumns()) && IsAdjacent(row, col) && ShiftGrid(row, col)) {
		std::cout << "The grid has been shifted to accommodate the new position.\n";
	}

	if (row >= 0 && row < size && col >= 0 && col < size) {
		if (grid[row][col].has_value() && !grid[row][col]->empty()) {
			std::cout << "The selected position is already occupied. Try again.\n";
			return false;
		}

		if (firstCardPlaced && !IsAdjacent(row, col)) {
			std::cout << "The selected position is not adjacent to an existing card. Try again.\n";
			return false;
		}

		illusionPositions.push_back({ row, col });
		illusionCards[{row, col}] = cardValue;

		grid[row][col] = std::make_optional<std::stack<card>>();
		grid[row][col]->push({ playerId, -1 });

		if (!firstCardPlaced) {
			firstCardPlaced = true;
		}
		return true;
	}
	return false;
}

void Board::ActivateExplosion(Player& player, Player& other) {
	if (!CanActivateExplosion()) return;

	srand(time(0));
	ExplosionPattern explosion(size);

	std::cout << "Generated explosion pattern at 0 degrees:\n";
	explosion.Display();

	ExplosionPattern initialExplosion = explosion;

	for (int rotation : {90, 180, 270}) {
		explosion = initialExplosion;
		explosion.Rotate(rotation);
		std::cout << "Explosion pattern at " << rotation << " degrees:\n";
		explosion.Display();
	}

	int chosenRotation = -1;
	while (chosenRotation != 0 && chosenRotation != 90 && chosenRotation != 180 && chosenRotation != 270) {
		std::cout << "Choose rotation (0, 90, 180, 270): ";
		std::cin >> chosenRotation;
	}

	explosion = initialExplosion;
	if (chosenRotation > 0) {
		explosion.Rotate(chosenRotation);
	}

	int centerRow = 1, centerCol = 1;
	Explosion explosionEffect;
	for (const auto& [rowOffset, colOffset] : explosion.GetAffectedPositions()) {
		int affectedRow = centerRow + rowOffset;
		int affectedCol = centerCol + colOffset;

		if (affectedRow >= 0 && affectedRow < size && affectedCol >= 0 && affectedCol < size) {
			if (explosion.IsHole(rowOffset + 1, colOffset + 1)) {
				explosionEffect.affectedPositions.push_back({ affectedRow, affectedCol });
				explosionEffect.effects.push_back(ExplosionEffect::CreateHole);
			}
			else if (explosion.IsHand(rowOffset + 1, colOffset + 1)) {
				explosionEffect.affectedPositions.push_back({ affectedRow, affectedCol });
				explosionEffect.effects.push_back(ExplosionEffect::TakeHand);
			}
			else {
				explosionEffect.affectedPositions.push_back({ affectedRow, affectedCol });
				explosionEffect.effects.push_back(ExplosionEffect::RemoveCard);
			}
		}
	}

	ApplyExplosionEffects(explosionEffect, player, other);

	Display();
}

bool Board::CanActivateExplosion() const {
	int filledRows = 0, filledCols = 0;

	for (int i = 0; i < size; ++i) {
		if (std::all_of(grid[i].begin(), grid[i].end(), [](const std::optional<std::stack<card>>& cell) {
			return cell.has_value() && !cell->empty() && cell->top().second != 0;
			})) {
			filledRows++;
		}
	}

	for (int col = 0; col < size; ++col) {
		bool columnFilled = true;
		for (int row = 0; row < size; ++row) {
			if (!grid[row][col].has_value() || grid[row][col]->empty() || grid[row][col]->top().second == 0) {
				columnFilled = false;
				break;
			}
		}
		if (columnFilled) {
			filledCols++;
		}
	}

	return (filledRows == 2) || (filledCols == 2) || (filledRows == 1 && filledCols == 1);
}

int Board::CalculateCardValueSum(int playerId) const {
	int sum = 0;

	for (const auto& row : grid) {
		for (const auto& cell : row) {
			if (cell.has_value() && !cell->empty() && cell->top().first == playerId) {
				const card& topCard = cell->top();
				if (IsIllusionValue(topCard) || topCard.second == 5) {
					sum++;
				}
				else {
					sum += topCard.second;
				}
			}
		}
	}

	return sum;
}

bool Board::IsIllusion(int row, int col) const
{
	return std::find(illusionPositions.begin(), illusionPositions.end(), std::make_pair(row, col)) != illusionPositions.end();
}

bool Board::IsIllusionValue(card cell) const {
	return std::find(illusionPositions.begin(), illusionPositions.end(), std::make_pair(cell.first, cell.second)) != illusionPositions.end();
}

void Board::EliminateIllusions() {
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (grid[row][col].has_value() && !grid[row][col]->empty() && IsIllusionValue(grid[row][col]->top())) {
				illusionCards.erase({ row, col });

				illusionPositions.erase(
					std::remove(
						illusionPositions.begin(),
						illusionPositions.end(),
						std::make_pair(row, col)),
					illusionPositions.end()
				);

				grid[row][col].reset();
			}
		}
	}
}

bool Board::ActivateMagicPower(MagicPower power, int row, int col, int playerId, card optionalCard) {
	switch (power) {
	case MagicPower::RemoveOpponentCard:
		return RemoveOpponentCard(row, col, playerId);
	case MagicPower::RemoveLine: {
		if (col == -1) {
			return RemoveRow(row, playerId);
		}
		else {
			return RemoveColumn(col, playerId);
		}
	}
	case MagicPower::CoverOpponentCard:
		CoverOpponentCard(row, col, optionalCard);
		return true;
	case MagicPower::CreatePit:
		CreatePit(row, col);
		return true;
	case MagicPower::MoveStack:
		return MoveStack(row, col, optionalCard.first, optionalCard.second, playerId);
	case MagicPower::ExtraEterCard:
		return ExtraEterCard(row, col, playerId);
	case MagicPower::MoveOpponentStack:
		return MoveOpponentStack(row, col, optionalCard.first, optionalCard.second, playerId);
	case MagicPower::ShiftRowToEdge:
		return ShiftRowToEdge(row, col == 1);
	default:
		return false;
	}
}

bool Board::RemoveOpponentCard(int row, int col, int currentPlayerId) {
	if (row < 0 || row >= size || col < 0 || col >= size) {
		std::cout << "Invalid position! Out of bounds.\n";
		return false;
	}

	if (!grid[row][col].has_value() || grid[row][col]->empty()) {
		std::cout << "No stack present at the specified position.\n";
		return false;
	}

	std::stack<card>& stack = grid[row][col].value();
	card topCard = stack.top();

	int opponentId = (currentPlayerId == 1) ? 2 : 1;
	if (topCard.first != opponentId) {
		std::cout << "The top card does not belong to the opponent.\n";
		return false;
	}

	stack.pop(); 
	bool ownsCardBelow = false;
	card belowCard = stack.top();
	if (belowCard.first == currentPlayerId)
		ownsCardBelow = true;


	if (!ownsCardBelow) {
		std::cout << "No own card found below the opponent's card.\n";
		stack.push(topCard);
		return false;
	}

	std::cout << "Opponent's card removed successfully!\n";
	return true;
}

bool Board::RemoveRow(int row, int currentPlayerId) {
	for (int col = 0; col < size; ++col) {
		if (!grid[row][col].has_value() || grid[row][col]->empty()) {
			std::cout << "The row cannot be removed because not all positions are occupied.\n";
			return false;
		}
	}

	bool hasPlayerCard = false;
	for (int col = 0; col < size; ++col) {
		card topCard = grid[row][col]->top();
		if (topCard.first == currentPlayerId) {
			hasPlayerCard = true;
			break;
		}
	}

	if (!hasPlayerCard) {
		std::cout << "The row cannot be removed because none of the top cards belong to you.\n";
		return false;
	}

	for (int col = 0; col < size; ++col) {
		grid[row][col].reset();
	}

	return true;
}

bool Board::RemoveColumn(int col, int currentPlayerId) {
	for (int row = 0; row < size; ++row) {
		if (!grid[row][col].has_value() || grid[row][col]->empty()) {
			std::cout << "The column cannot be removed because not all positions are occupied.\n";
			return false;
		}
	}

	bool hasPlayerCard = false;
	for (int row = 0; row < size; ++row) {
		card topCard = grid[row][col]->top();
		if (topCard.first == currentPlayerId) {
			hasPlayerCard = true;
			break;
		}
	}

	if (!hasPlayerCard) {
		std::cout << "The column cannot be removed because none of the top cards belong to you.\n";
		return false;
	}

	for (int row = 0; row < size; ++row) {
		grid[row][col].reset();
	}

	return true;
}

void Board::CoverOpponentCard(int row, int col, card weakerCard) {
	if (row < 0 || row >= size || col < 0 || col >= size) {
		std::cout << "Invalid position! Out of bounds.\n";
		return;
	}

	if (!grid[row][col].has_value() || grid[row][col]->empty()) {
		std::cout << "No card to cover at the specified position.\n";
		return;
	}

	card topCard = grid[row][col]->top();

	int opponentId = (weakerCard.first == 1) ? 2 : 1;
	if (topCard.first != opponentId) {
		std::cout << "The top card does not belong to the opponent.\n";
		return;
	}

	if (weakerCard.second >= topCard.second) {
		std::cout << "Your card is not weaker than the opponent's card.\n";
		return;
	}

	grid[row][col]->push(weakerCard);
	std::cout << "Your weaker card successfully covered the opponent's card!\n";
}

void Board::CreatePit(int row, int col) {
	if (row < 0 || row >= size || col < 0 || col >= size) {
		std::cout << "Invalid position! Out of bounds.\n";
		return;
	}

	if (grid[row][col].has_value() && !grid[row][col]->empty()) {
		std::cout << "Cannot create a hole on an occupied space.\n";
		return;
	}

	grid[row][col] = std::make_optional<std::stack<card>>();
	std::cout << "Hole created successfully at (" << row << ", " << col << ").\n";
}

bool Board::MoveStack(int srcRow, int srcCol, int destRow, int destCol, int currentPlayerId) {
	if (srcRow < 0 || srcRow >= size || srcCol < 0 || srcCol >= size) {
		std::cout << "Invalid source position! Out of bounds.\n";
		return false;
	}

	if (!grid[srcRow][srcCol].has_value() || grid[srcRow][srcCol]->empty()) {
		std::cout << "No stack at the source position.\n";
		return false;
	}

	if (grid[srcRow][srcCol]->top().first != currentPlayerId) {
		std::cout << "The top card does not belong to you.\n";
		return false;
	}

	if (destRow < 0 || destRow >= size || destCol < 0 || destCol >= size) {
		std::cout << "Invalid destination position! Out of bounds.\n";
		return false;
	}

	if (grid[destRow][destCol].has_value() && !grid[destRow][destCol]->empty()) {
		std::cout << "Destination position is not empty.\n";
		return false;
	}

	grid[destRow][destCol] = std::move(grid[srcRow][srcCol]);
	grid[srcRow][srcCol].reset();

	if (!IsBoardConnected()) {
		grid[srcRow][srcCol] = std::move(grid[destRow][destCol]);
		grid[destRow][destCol].reset();
		std::cout << "Move failed: it would isolate parts of the board.\n";
		return false;
	}

	std::cout << "Stack moved successfully from (" << srcRow << ", " << srcCol
		<< ") to (" << destRow << ", " << destCol << ").\n";

	return true;
}

//commit

bool Board::ExtraEterCard(int row, int col, int playerId) {
	if (row < 0 || row >= size || col < 0 || col >= size) {
		std::cout << "Invalid position! Out of bounds.\n";
		return false;
	}

	if (grid[row][col].has_value() && !grid[row][col]->empty()) {
		std::cout << "Cannot place an Eter card on an occupied space.\n";
		return false;
	}

	if (!grid[row][col].has_value()) {
		grid[row][col] = std::make_optional<std::stack<card>>();
	}

	grid[row][col]->push({ playerId, 5 }); // 5 represents the Eter card value
	std::cout << "Eter card placed successfully at (" << row << ", " << col << ").\n";
	return true;
}//commit


//commit
bool Board::MoveOpponentStack(int srcRow, int srcCol, int destRow, int destCol, int currentPlayerId) {
	if (srcRow < 0 || srcRow >= size || srcCol < 0 || srcCol >= size) {
		std::cout << "Invalid source position! Out of bounds.\n";
		return false;
	}

	if (!grid[srcRow][srcCol].has_value() || grid[srcRow][srcCol]->empty()) {
		std::cout << "No stack at the source position.\n";
		return false;
	}

	int opponentId = (currentPlayerId == 1) ? 2 : 1;
	if (grid[srcRow][srcCol]->top().first != opponentId) {
		std::cout << "The top card does not belong to the opponent.\n";
		return false;
	}

	if (destRow < 0 || destRow >= size || destCol < 0 || destCol >= size) {
		std::cout << "Invalid destination position! Out of bounds.\n";
		return false;
	}

	if (grid[destRow][destCol].has_value() && !grid[destRow][destCol]->empty()) {
		std::cout << "Destination position is not empty.\n";
		return false;
	}

	grid[destRow][destCol] = std::move(grid[srcRow][srcCol]);
	grid[srcRow][srcCol].reset();

	if (!IsBoardConnected()) {
		grid[srcRow][srcCol] = std::move(grid[destRow][destCol]);
		grid[destRow][destCol].reset();
		std::cout << "Move failed: it would isolate parts of the board.\n";
		return false;
	}

	std::cout << "Stack moved successfully from (" << srcRow << ", " << srcCol
		<< ") to (" << destRow << ", " << destCol << ").\n";
	return true;
}//commit


//commit
bool Board::ShiftRowToEdge(int index, bool isHorizontal) {
	if (index < 0 || index >= size) {
		std::cout << "Invalid index! Out of bounds.\n";
		return false;
	}

	int count = 0;
	for (int i = 0; i < size; ++i) {
		if (isHorizontal) {
			if (grid[index][i].has_value() && !grid[index][i]->empty()) {
				count++;
			}
		}
		else {
			if (grid[i][index].has_value() && !grid[i][index]->empty()) {
				count++;
			}
		}
	}

	if (count < 3) {
		std::cout << "The selected row or column does not have at least 3 cards.\n";
		return false;
	}

	if (isHorizontal) {
		std::vector<std::optional<std::stack<card>>> temp = grid[index];
		grid.erase(grid.begin() + index);
		if (index == 0) {
			grid.push_back(temp); 
		}
		else {
			grid.insert(grid.begin(), temp); 
		}
	}
	else {
		std::vector<std::optional<std::stack<card>>> temp(size);
		for (int i = 0; i < size; ++i) {
			temp[i] = grid[i][index];
			grid[i].erase(grid[i].begin() + index);
		}

		if (index == 0) {
			for (int i = 0; i < size; ++i) {
				grid[i].push_back(temp[i]);
			}
		}
		else {
			for (int i = 0; i < size; ++i) {
				grid[i].insert(grid[i].begin(), temp[i]); 
			}
		}
	}

	std::cout << "Row/column " << index << " successfully moved to the opposite edge.\n";

	return true;
}//commit

//commit

bool Board::IsBoardConnected() const {
	std::pair<int, int> start = { -1, -1 };
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (grid[row][col].has_value() && !grid[row][col]->empty()) {
				start = { row, col };
				break;
			}
		}
		if (start.first != -1) break;
	}

	if (start.first == -1) {
		return true;
	}

	std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));
	std::queue<std::pair<int, int>> q;
	q.push(start);
	visited[start.first][start.second] = true;

	int connectedCells = 0;
	int totalCells = 0;

	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (grid[row][col].has_value() && !grid[row][col]->empty()) {
				totalCells++;
			}
		}
	}

	int directions[8][2] = {
		{-1, 0}, {1, 0}, {0, -1}, {0, 1}, 
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1}
	};

	while (!q.empty()) {
		auto [row, col] = q.front();
		q.pop();
		connectedCells++;

		for (auto& dir : directions) {
			int newRow = row + dir[0];
			int newCol = col + dir[1];

			if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size &&
				!visited[newRow][newCol] &&
				grid[newRow][newCol].has_value() && !grid[newRow][newCol]->empty()) {
				visited[newRow][newCol] = true;
				q.push({ newRow, newCol });
			}
		}
	}

	return connectedCells == totalCells;
}//commit

