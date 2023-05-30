#pragma once

#include "Pieces.hpp"

class King : public Pieces
{
public:
	// Constructor
	King(Player player);

	// Destructor
	~King() override;

	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;

private:
	bool hasMoved;
};