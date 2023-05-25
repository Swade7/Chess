#pragma once

#include "Pieces.hpp"

class Knight : public Pieces
{
	bool checkValidMove(const Move& move, const Chess& board) const override;
	void movePiece(const Move& move, Chess& board) override;
};