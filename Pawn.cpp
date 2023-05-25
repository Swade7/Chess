#include "Pawn.hpp"

bool Pawn::checkValidMove(const Move& move, const Chess& board) const
{
	return false;
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
