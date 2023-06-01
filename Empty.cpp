#include "Empty.hpp"

// Constructor
Empty::Empty()
	: Pieces(PieceType::Empty, Player::None)
{}

// Destructor
Empty::~Empty() = default;

bool Empty::checkValidMove(const Move& move, const Chess& chess) const
{
	return false;
}

void Empty::movePiece(const Move& move, Chess& chess)
{
	// Add output telling user that the location is empty
}
