#pragma once

#include "Pieces.hpp"

class Rook : public Pieces
{
public:
	// Constructor
	Rook(Player player);
	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;
};