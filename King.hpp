#pragma once

#include "Pieces.hpp"

class King : public Pieces
{
public:
	// Constructor
	King(Player player);

	// Destructor
	~King() override;

	// Copy
	King* clone() const override;

	// Getters
	const PieceType& getPieceType() const override;
	const Player& getPlayer() const override;

	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const override;
	void updatePiece() override;

private:
	bool hasMoved;
	Player player;
};