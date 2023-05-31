#pragma once

#include "Pieces.hpp"

class Rook : public Pieces
{
public:
	// Constructor
	Rook(Player player);

	// Destructor
	~Rook() override;

	// Overriden functions
	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;

	// Getters
	const bool getHasMoved() const;

private:
	bool hasMoved;
};