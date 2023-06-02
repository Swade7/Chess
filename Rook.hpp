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

	// Overriden functions
	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) const override;
	void movePiece(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) override;

	

private:
	bool hasMoved;
};