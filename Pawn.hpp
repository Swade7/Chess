#pragma once

#include "Pieces.hpp"

class Pawn : public Pieces
{
public:
	// Constructor
	Pawn(Player player);

	// Destructor
	~Pawn() override;

	// Getters
	const PieceType& getPieceType() const override;

private:
	// Overridden functions
	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;

};