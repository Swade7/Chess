#pragma once

#include "Pieces.hpp"

class Empty : public Pieces
{
public:
	// Constructor
	Empty();

	// Destructor
	~Empty() override;

	// Getters
	const PieceType& getPieceType() const override;

	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;
};