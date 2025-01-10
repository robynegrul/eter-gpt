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
				grid[row][col] = std::make_optional<std::stack<card>>(std::stack<card>{});
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
					grid[row][col].reset();  // Reset to nullopt if the stack is empty
				}
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
