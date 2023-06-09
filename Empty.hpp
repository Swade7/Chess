#pragma once

#include "Pieces.hpp"

class Empty : public Pieces
{
public:
	// Constructor
	Empty();

	// Destructor
	~Empty() override;

	// Copy
	Empty* clone() const override;

	// Getters
	const PieceType& getPieceType() const override;
	const Player& getPlayer() const override;

	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const override;
	void updatePiece() override;

private:
	Player player;
};