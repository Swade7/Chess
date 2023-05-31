#include "King.hpp"

King::King(Player player)
	: Pieces(PieceType::King, player)
{
	hasMoved = false;
}

King::~King() = default;

bool King::checkValidMove(const Move& move, const Chess& chess) const
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

	// King specific checks
	// Check if trying to castle
	if (!hasMoved && std::abs(move.fromCol - move.toCol) == 2 && move.fromRow == move.toRow)
	{

		// Get the col of the rook
		int rookCol;
		if (move.fromCol > move.toCol)
		{
			rookCol = 0;
		}
		else if (move.fromCol < move.toCol)
		{
			rookCol = 7;
		}

		// Get the Row of the rook
		int rookRow;
		if (board[move.fromCol][move.fromRow]->getPlayer() == Player::White)
		{
			rookRow = 0;
		}
		else if (board[move.fromCol][move.fromRow]->getPlayer() == Player::Black)
		{
			rookRow = 7;
		}

		// Check if the rook has been moved
		if (board[rookCol][rookRow]->getPieceType() != PieceType::Rook)
		{
			return false;
		}
		else
		{
			const Rook* rook = dynamic_cast<const Rook*>(board[rookCol][rookRow]);
			if (rook->getHasMoved())
			{
				return false;
			}
		}

		// Check if any place being moved through or the king's current position would be in check
		/*
		* for (int i = std::min(move.fromCol, rookCol); i <= std::max(move.fromCol, rookCol); i++)
		if (check(i, move.fromRow) && i != rookCol)
		{
			return false;
		}
		*/
	

		// Check if all spaces between the two pieces are empty
		for (int i = std::min(move.fromCol, rookCol) + 1; i < std::max(move.fromCol, rookCol); i++)
		{
			if (board[i][rookRow]->getPieceType() != PieceType::Empty)
			{
				return false;
			}
		}

	// Prevent the king from moving more than one space 
	if (std::abs(move.toCol - move.fromCol) > 1 || std::abs(move.toRow - move.fromRow) > 1)
	{
		return false;
	}

	return true;
}

void King::movePiece(const Move& move, Chess& chess)
{
	if (checkValidMove(move, chess))
	{
		chess.updateBoard(move);
	}

	// Set the hasMoved variable to true
	hasMoved = true;
}

