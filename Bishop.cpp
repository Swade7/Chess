#include "Bishop.hpp"


// Constructor
Bishop::Bishop(Player player)
	: Pieces(PieceType::Bishop, player)
{
	this->player = player;
}

// Destructor
Bishop::~Bishop() = default;

// Copy
Bishop* Bishop::clone() const
{
	return new Bishop(*this);
}

// Getters
const PieceType& Bishop::getPieceType() const
{
	return PieceType::Bishop;
}
const Player& Bishop::getPlayer() const
{
	return player;
}

bool Bishop::checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const
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

	// Bishop specific checks
	int rowDifference = std::abs(move.toRow - move.fromRow);
	int colDifference = std::abs(move.toCol - move.fromCol);

	if (rowDifference != colDifference)
	{
		return false;
	}

	// Check for pieces blocking the path
	if (move.toCol > move.fromCol)
	{
		if (move.toRow > move.fromRow)
		{
			for (int i = move.fromCol + 1; i < move.toCol; i++)
			{
				if (board[i][move.fromRow + (i - move.fromCol)]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
		// move.toRow < move.fromRow
		else
		{
			for (int i = move.fromCol + 1; i < move.toCol; i++)
			{
				if (board[i][move.fromRow - (i - move.fromCol)]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
	}  
	// move.toCol < move.fromCol
	else
	{
		if (move.toRow > move.fromRow)
		{
			for (int i = move.fromRow + 1; i < move.toRow; i++)
			{
				if (board[i][move.fromCol - (i - move.fromRow)]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
		// move.toRow < move.fromRow
		else
		{
			for (int i = move.toCol + 1; i < move.fromCol; i++)
			{
				if (board[i][move.toRow + (i - move.toCol)]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Bishop::updatePiece() {};