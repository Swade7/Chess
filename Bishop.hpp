#pragma once

#include "ChessLogic.hpp"

class Bishop : public Pieces
{
public:
	// Constructor
	Bishop(Player player);
	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;
};