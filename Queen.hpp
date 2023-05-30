#pragma once

#include "Pieces.hpp"

class Queen : public Pieces
{
	bool checkValidMove(const Move& move, const Chess& chess) const override;
	bool checkValidStraightMove(const Move& move, const Chess& chess) const;
	bool checkValidDiagonalMove(const Move& move, const Chess& chess) const;
	void movePiece(const Move& move, Chess& chess) override;
};