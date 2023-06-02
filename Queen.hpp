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

	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) const override;
	void movePiece(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) override;

private:
	bool checkValidStraightMove(const Move& move, const Chess& chess) const;
	bool checkValidDiagonalMove(const Move& move, const Chess& chess) const;
	
};