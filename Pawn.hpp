#pragma once

#include "Pieces.hpp"

class Pawn : public Pieces
{

	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;
};