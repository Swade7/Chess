#include "Empty.hpp"

// Constructor
Empty::Empty()
	: Pieces(PieceType::Empty, Player::None)
{}

// Destructor
Empty::~Empty() = default;

// Getters
const PieceType& Empty::getPieceType() const
{
	return PieceType::Empty;
}

bool Empty::checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const
{
	return false;
}

void Empty::updatePiece() {};
