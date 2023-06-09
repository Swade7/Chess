#pragma once

#include "Pieces.hpp"

class Knight : public Pieces
{
public:
	// Constructor
	Knight(Player player);

	// Destructor
	~Knight() override;

	// Copy
	Knight* clone() const override;

	// Getters
	const PieceType& getPieceType() const override;
	const Player& getPlayer() const override;

	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const override;
	void updatePiece() override;

	Player player;
};