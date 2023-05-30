#pragma once

#include "Pieces.hpp"

class Queen : public Pieces
{
public:
	// Constructor
	Queen(Player player);

	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;

private:
	bool checkValidStraightMove(const Move& move, const Chess& chess) const;
	bool checkValidDiagonalMove(const Move& move, const Chess& chess) const;
	
};