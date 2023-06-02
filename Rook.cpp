#include "Rook.hpp"


// Constructor
Rook::Rook(Player player)
	: Pieces(PieceType::Rook, player)
{
	hasMoved = false;
}

// Destructor
Rook::~Rook() = default;

bool Rook::checkValidMove(const Move& move, const Chess& chess) const
{
	// Check if the move is out of bounds
	if (move.toRow > BOARD_SIZE - 1 || move.toRow < 0 || move.toCol > BOARD_SIZE - 1 || move.toCol < 0)
	{
		return false;
	}

	// Get the board
	Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

	// Check if the piece belongs to the current player
	if (board[move.fromCol][move.fromRow]->getPlayer() != chess.getCurrentPlayer())
	{
		return false;
	}

	// Check if the space to be moved to is already occupied by the current player's piece
	if (board[move.toCol][move.toRow]->getPlayer() == chess.getCurrentPlayer())
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
		// Right
		if (move.toRow > move.fromRow)
		{
			for (int i = move.fromRow; i < move.toRow; i++)
			{
				if (board[i][move.fromCol]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
		// Left
		else if (move.toRow < move.fromRow)
		{
			for (int i = move.toRow; i < move.fromRow; i++)
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
			for (int i = move.fromCol; i < move.toCol; i++)
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
			for (int i = move.toCol; i < move.fromCol; i++)
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

void Rook::movePiece(const Move& move, Chess& chess)
{
	if (checkValidMove(move, chess))
	{
		chess.updateBoard(move);
	}

	// Update hasMoved to true
	hasMoved = true;
}

const bool Rook::getHasMoved() const
{
	return hasMoved;
}
