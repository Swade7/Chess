#pragma once

#include "Pieces.hpp"

class Queen : public Pieces
{
public:
	// Constructor
	Queen(Player player);

	// Destructor
	~Queen() override;

	// Getters
	const PieceType& getPieceType() const override;

	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const override;
	void updatePiece() override;

private:
	bool checkValidStraightMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) const;
	bool checkValidDiagonalMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) const;
};