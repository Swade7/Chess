#pragma once

#include "Pieces.hpp"

class King : public Pieces
{
public:
	// Constructor
	King(Player player);

	// Destructor
	~King() override;

	// Getters
	const PieceType& getPieceType() const override;

	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) const override;
	void movePiece(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) override;

private:
	bool hasMoved;
};