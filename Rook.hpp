#pragma once

#include "Pieces.hpp"

class Rook : public Pieces
{
public:
	// Constructor
	Rook(Player player);

	// Destructor
	~Rook() override;

	// Getters
	const bool getHasMoved() const;
	const PieceType& getPieceType() const override;

	// Overriden functions
	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;

	

private:
	bool hasMoved;
};