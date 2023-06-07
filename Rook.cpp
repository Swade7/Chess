#include "Rook.hpp"


// Constructor
Rook::Rook(Player player)
	: Pieces(PieceType::Rook, player)
{
	hasMoved = false;
}

// Destructor
Rook::~Rook() = default;

bool Rook::checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const
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

	// Rook specific checks
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
		// Up
		if (move.toRow > move.fromRow)
		{
			for (int i = move.fromRow + 1; i < move.toRow; i++)
			{
				if (board[i][move.fromCol]->getPlayer() != Player::None)
				{
					std::cout << i << ", " << move.fromCol << " is occupied by ";
					if (board[i][move.fromCol]->getPlayer() == Player::White)
						std::cout << "White" << std::endl;
					if (board[i][move.fromCol]->getPlayer() == Player::Black)
						std::cout << "Black" << std::endl;
					return false;
				}
			}
		}
		// Left
		else if (move.toRow < move.fromRow)
		{
			for (int i = move.toRow + 1; i < move.fromRow; i++)
			{
				if (board[i][move.fromCol]->getPlayer() != Player::None)
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
				if (board[move.fromRow][i]->getPlayer() != Player::None)
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
				if (board[move.fromRow][i]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Rook::updatePiece()
{
	hasMoved = true;
}

const bool Rook::getHasMoved() const
{
	return hasMoved;
}

const PieceType& Rook::getPieceType() const
{
	return PieceType::Rook;
}
