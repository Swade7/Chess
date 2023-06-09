#include "Queen.hpp"


// Constructor
Queen::Queen(Player player)
	: Pieces(PieceType::Queen, player)
{
	this->player = player;
}

// Destructor
Queen::~Queen() = default;

// Copy
Queen* Queen::clone() const
{
	return new Queen(*this);
}

// Getters
const PieceType& Queen::getPieceType() const
{
	return PieceType::Queen;
}

const Player& Queen::getPlayer() const
{
	return player;
}

bool Queen::checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const
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

	if (move.fromCol != move.toCol && move.fromRow != move.toRow)
	{
		return checkValidDiagonalMove(move, board);
	}
	else
	{
		return checkValidStraightMove(move, board);
	}
}

bool Queen::checkValidStraightMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) const
{
	// Check if trying to move diagonally
	if (move.toCol != move.fromCol && move.toRow != move.fromRow)
	{
		return false;
	}

	// Determine if moving vertically or horizontally
	char dir;
	if (move.fromCol == move.toCol)
	{
		dir = 'v';
	}
	else
	{
		dir = 'h';
	}

	// Check if another piece is blocking the path
	// Checks for vertical movements
	if (dir == 'v')
	{
		// Down
		if (move.toRow > move.fromRow)
		{

			for (int i = move.fromRow + 1; i < move.toRow; i++)
			{
				if (board[move.fromCol][i]->getPlayer() != Player::None || board[move.fromCol][i]->getPieceType() != PieceType::Empty)
				{
					return false;
				}
			}
		}
		// Up
		else if (move.toRow < move.fromRow)
		{
			for (int i = move.toRow + 1; i < move.fromRow; i++)
			{
				if (board[move.fromCol][i]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
	}
	// Checks for horizontal movements
	else if (dir == 'h')
	{
		// Right
		if (move.toCol > move.fromCol)
		{
			for (int i = move.fromCol + 1; i < move.toCol; i++)
			{
				if (board[i][move.fromRow]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
		// Left
		else if (move.toCol < move.fromCol)
		{
			for (int i = move.toCol + 1; i < move.fromCol; i++)
			{
				if (board[i][move.fromRow]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Queen::checkValidDiagonalMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE]) const
{
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
			for (int i = move.toCol + 1; i < move.fromCol; i++)
			{
				if (board[i][move.toRow - (i - move.fromRow)]->getPlayer() != Player::None)
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

void Queen::updatePiece() {};