#pragma once

#include "Pieces.hpp"

class Bishop : public Pieces
{
public:
	// Constructor
	Bishop(Player player);

	// Destructor
	~Bishop() override;

	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;
};