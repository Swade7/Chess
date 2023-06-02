#pragma once

#include "Pieces.hpp"

class Knight : public Pieces
{
public:
	// Constructor
	Knight(Player player);

	// Destructor
	~Knight() override;

	// Getters
	const PieceType& getPieceType() const override;

	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;
};