#pragma once

#include "Pieces.hpp"

class Pawn : public Pieces
{
public:
	// Constructor
	Pawn(Player player);

	// Destructor
	~Pawn() override;

	// Copy
	Pawn* clone() const override;

	// Getters
	const PieceType& getPieceType() const override;
	const Player& getPlayer() const override;

	// Overridden functions
	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const override;
	void updatePiece() override;

private:
	Player player;
};