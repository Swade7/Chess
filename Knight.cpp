#include "knight.hpp"

bool Knight::checkValidMove(const Move& move, const Chess& chess) const
{
	// Get the board
	const Piece(&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

	// Check if the piece belongs to the current player
	if (board[move.fromCol][move.fromRow].player != chess.getCurrentPlayer())
	{
		return false;
	}

	// Check if the space to be moved to is already occupied by the current player's piece
	if (board[move.toCol][move.toRow].player == chess.getCurrentPlayer())
	{
		return false;
	}

	// Check if the move is out of bounds
	else if (move.toRow > 7 || move.toRow < 0 || move.toCol > 7 || move.toCol < 0)
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

void Knight::movePiece(const Move& move, Chess& chess)
{
	if (checkValidMove(move, chess))
	{
		chess.updateBoard(move);
	}
}
