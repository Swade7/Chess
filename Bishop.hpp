#pragma once

#include "Pieces.hpp"

class Bishop : public Pieces
{
public:
	// Constructor
	Bishop(Player player);

	// Destructor
	~Bishop() override;

	// Getters
	const PieceType& getPieceType() const override;
	const Player& getPlayer() const override;

	bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const override;
	void updatePiece() override;

private:
	Player player;
};