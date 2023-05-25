#include "Pawn.hpp"

bool Pawn::checkValidMove(const Move& move, const Chess& chess) const
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

	// Make sure they are actually moving
	else if (move.fromCol == move.toCol && move.toRow == move.fromRow)
	{
		return false;
	}
}

void Pawn::movePiece(const Move& move, Chess& chess)
{
	if (checkValidMove(move))
	{
		// If a piece is captured, add it to the correct vector
		if (chess.board[move.toCol][move.toRow].player == Player::White)
		{
			Pieces::capturedWhitePieces.push_back(board[move.toCol][move.toRow].pieceType);
		}
		else if (board[move.toCol][move.toRow].player == Player::Black)
		{
			capturedBlackPieces.push_back(board[move.toCol][move.toRow].pieceType);
		}

		// Update the board
		board[move.toCol][move.toRow].moved = true;
		board[move.toCol][move.toRow].pieceType = board[move.fromCol][move.fromRow].pieceType;
		board[move.toCol][move.toRow].player = board[move.fromCol][move.fromRow].player;
		board[move.fromCol][move.fromRow].moved = true;
}