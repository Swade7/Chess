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

	int maxDistance;
	if (currentPlayer == Player::White)
	{
		// If the player has not moved the pawn yet, allow them to move one or two places, else, allow them to move it only one place
		if (move.fromRow == 2)
		{
			maxDistance = 2;
		}
		else
		{
			maxDistance = 1;
		}
		// Check if not moving forward
		if ((move.toRow <= move.fromRow) || (maxDistance < (move.toRow - move.fromRow)))
		{
			return false;
		}

		// Only allow horizontal moves if capturing
		if (move.toCol != move.fromCol)
		{
			if (board[move.toCol][move.toRow]->getPlayer() != Player::Black)
			{
				if (move.fromRow != 4 || (board[move.toCol][move.fromRow]->getPieceType() != PieceType::Pawn && board[move.toCol][move.fromRow]->getPlayer() != Player::Black))
					return false;
			}
		}

		// Check if the location is already occupied if not capturing
		else if (board[move.toCol][move.toRow]->getPlayer() != Player::None)
		{
			return false;
		}

		// If moving two places, make sure the piece is not moving through another piece
		else if (move.toRow - move.fromRow == 2 && board[move.toCol][move.toRow - 1]->getPlayer() != Player::None)
		{
			return false;
		}

		return true;
	}

	else if (currentPlayer == Player::Black)
	{
		// Allow movements of 1 or 2 places if the pawn has not been moved yet, else, only allow 1
		if (move.fromRow == 7)
		{
			maxDistance = -2;
		}
		else
		{
			maxDistance = -1;
		}

		// Check if the location is invalid
		if ((move.toRow >= move.fromRow) || (maxDistance < (move.toRow - move.fromRow)))
		{

			return false;
		}

		// Only allow horizontal moves if capturing
		if (move.toCol != move.fromCol)
		{
			if (board[move.toCol][move.toRow]->getPlayer() != Player::White)
			{
				// Check for en passant
				if (board[move.toCol][move.toRow]->getPieceType() != PieceType::Pawn)
				{
					return false;
				}
				else
				{
					if (lastMove.fromCol != move.toCol || lastMove.fromRow != move.toRow - 1 || lastMove.toCol != move.toCol || lastMove.toRow != move.fromRow)
					{
						return false;
					}
				}
			}
		}

		// If not capturing, make sure the location is empty
		else if (board[move.toCol][move.toRow]->getPlayer() != Player::None && move.toCol == move.fromCol)
		{
			return false;
		}

		// If moving two places, make sure the piece is not moving through another piece
		else if (move.fromRow - move.toRow == 2 && board[move.toRow + 1][move.toCol]->getPlayer() != Player::None)
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

void Pawn::updatePiece() {};