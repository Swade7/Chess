#include "knight.hpp"


// Constructor
Knight::Knight(Player player)
	: Pieces(PieceType::Knight, player){}

// Destructor
Knight::~Knight() = default;

// Getters
const PieceType& Knight::getPieceType() const
{
	return PieceType::Knight;
}

bool Knight::checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const
{
	// Check if the move is out of bounds
	if (move.toRow > BOARD_SIZE - 1 || move.toRow < 0 || move.toCol > BOARD_SIZE - 1 || move.toCol < 0)
	{
		return false;
	}

	// Check if the piece belongs to the current player
	if (board[move.fromCol][move.fromRow]->getPlayer() != currentPlayer)
	{
		return false;
	}

	// Check if the space to be moved to is already occupied by the current player's piece
	if (board[move.toCol][move.toRow]->getPlayer() == currentPlayer)
	{
		return false;
	}

	// Knight specific checks
	int rowDifference = std::abs(move.toRow - move.fromRow);
	int colDifference = std::abs(move.toCol - move.fromCol);

	if (rowDifference == 1 && colDifference == 2 || colDifference == 1 && rowDifference == 2)
	{
		return true;
	}

	return false;
}

void Knight::updatePiece() {};