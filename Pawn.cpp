#include "Pawn.hpp"

// Constructor
Pawn::Pawn(Player player)
	: Pieces(PieceType::Pawn, player){}

Pawn::~Pawn() = default;

// getters
const PieceType& Pawn::getPieceType() const
{
	return PieceType::Pawn;
}

bool Pawn::checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const
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

	// Make sure they are actually moving
	else if (move.fromCol == move.toCol && move.toRow == move.fromRow)
	{
		return false;
	}

	// Pawn specific checks
	// Get the direction the player's pawns can move, the pawns starting location, and get the opponent's piece color
	int dir, startingRow = 0;
	Player opponent = Player::None;
	if (currentPlayer == Player::White)
	{
		dir = 1;
		startingRow = 1;
		opponent = Player::Black;
	}
	else if (currentPlayer == Player::Black)
	{
		dir = -1;
		startingRow = 6;
		opponent = Player::White;
	}
	else
	{
		return false;
	}

	// If the player has not moved the pawn yet, allow them to move one or two places, else, allow them to move it only one place
	int maxDistance;
	if (move.fromRow == startingRow)
	{
		maxDistance = 2 * dir;
	}
	else
	{
		maxDistance = 1 * dir;
	}

	// Check if the player attempts to make a horizontal move, if capturing correctly, allow, else, block
	if (move.fromRow == move.toRow)
	{
		return false;
	}
	// Check if move is  < 1 or > -1 horizontally
	else if (std::abs(move.fromCol - move.toCol) > 1)
	{
		return false;
	}

	// Check if not moving forward
	if (currentPlayer == Player::White)
	{
		if ((move.toRow <= move.fromRow) || (maxDistance < (move.toRow - move.fromRow)))
		{
			return false;
		}
	}
	else if (currentPlayer == Player::Black)
	{

		if ((move.toRow >= move.fromRow) || (std::abs(maxDistance) < (move.fromRow - move.toRow)))
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	// Only allow horizontal moves if capturing
	if (move.toCol != move.fromCol)
	{
		// Check for en passant capturing
		if (board[move.toCol][move.toRow]->getPlayer() != opponent)
		{
			if (move.fromRow != startingRow + (3 * dir) || board[move.toCol][move.fromRow]->getPieceType() != PieceType::Pawn)
			{
				std::cout << "First check";
				return false;
			}
				
			if (lastMove.fromCol != move.toCol || lastMove.toRow != move.toRow - dir || lastMove.toCol != move.toCol || lastMove.toRow != move.fromRow)
			{
				std::cout << "Second check";
				return false;				
			}
		}
	}
	
	// Check if the location is already occupied if not capturing
	else if (board[move.toCol][move.toRow]->getPlayer() != Player::None)
	{
		return false;
	}

	// If moving two places, make sure the piece is not moving through another piece
	else if (move.toRow - move.fromRow == (2 * dir) && board[move.toCol][move.toRow - dir]->getPlayer() != Player::None)
	{
		return false;
	}
	return true;
}

void Pawn::updatePiece() {};