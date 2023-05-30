#include "Bishop.hpp"

// Constructor
Bishop::Bishop(Player player)
	: Pieces(PieceType::Bishop, player)
{
}

// Destructor
Bishop::~Bishop() = default;

bool Bishop::checkValidMove(const Move& move, const Chess& chess) const
{
	// Check if the move is out of bounds
	if (move.toRow > BOARD_SIZE - 1 || move.toRow < 0 || move.toCol > BOARD_SIZE - 1 || move.toCol < 0)
	{
		return false;
	}

	// Get the board
	const Pieces* (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

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
			for (int i = move.fromRow + 1; i < move.toRow; i++)
			{
				if (board[i][move.fromCol + (i - move.fromRow)]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
		else
		{
			for (int i = move.fromRow - 1; i > move.toRow; i--)
			{
				if (board[i][move.fromCol + (i - move.fromRow)]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
	}  
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
		else
		{
			for (int i = move.fromRow - 1; i > move.toRow; i--)
			{
				if (board[i][move.fromCol - (i - move.fromRow)]->getPlayer() != Player::None)
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Bishop::movePiece(const Move& move, Chess& chess)
{
	if (checkValidMove(move, chess))
	{
		chess.updateBoard(move);
	}
}
