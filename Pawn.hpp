#pragma once

#include "Pieces.hpp"

class Pawn : public Pieces
{
public:
	// Constructor
	Pawn(Player player);

	// Setters
	void PreventEnPassant();

	// Getters
	bool getEnPassant();

private:
	// Overridden functions
	bool checkValidMove(const Move& move, const Chess& chess) const override;
	void movePiece(const Move& move, Chess& chess) override;

	// Boolean checks
	bool hasMoved;
	int enPassant;
};