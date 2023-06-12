#pragma once

#include "Pieces.hpp"

class Rook : public Pieces
{
public:
	// Constructor
	Rook(Player player);

	// Destructor
	~Rook() override;

	// Getters
	const bool getHasMoved() const;
	const PieceType& getPieceType() const override;
	const Player& getPlayer() const override;

	// Overriden functions
	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const override;
	void updatePiece() override;

private:
	bool hasMoved;
	Player player;
};