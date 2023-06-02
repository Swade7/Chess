#pragma once

#include "Pieces.hpp"

class Empty : public Pieces
{
public:
	// Constructor
	Empty();

	// Destructor
	~Empty() override;

	// Getters
	const PieceType& getPieceType() const override;

	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const override;
	void updatePiece() override;
};