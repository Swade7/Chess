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
		// White
		if (board[move.fromCol][move.fromRow]->getPieceType() == PieceType::Empty)
		{
			// Left rook
			if (move.toCol < move.fromCol)
			{
				for (int i = move.fromCol; i > 0; i--)
				{
					//if (check(board[i][move.fromRow] && i >= move.toCol)
					//{
					//	return false;
					//}

					if (board[i][move.fromRow]->getPieceType() != PieceType::Empty)
					{
						return false;
					}
				}
				vector<Move> moves = chess.getMoves();
				for (int i = 0; i < moves.size(); i++)
				{
					if (moves.at(i).fromCol == 0 && moves.at(i).fromRow == 0)
					{
						return false;
					}
				}

			}
			// Right rook
			else
			{
				for (int i = move.fromCol; i < 7; i++)
				{
					//if (check(board[i][move.fromRow] && i <= move.toCol)
					//{
					//	return false;
					//}
					if (board[i][move.fromRow]->getPieceType() != PieceType::Empty)
					{
						return false;
					}
				}
				vector<Move> moves = chess.getMoves();
				for (int i = 0; i < moves.size(); i++)
				{
					if (moves.at(i).fromCol == 7 && moves.at(i).fromRow == 0)
					{
						return false;
					}
				}
			}
		}

		// Black
		else 
		{
			// Left rook
			if (move.toCol < move.fromCol)
			{
				for (int i = move.fromCol; i > 0; i--)
				{
					//if (check(board[i][move.fromRow] && i >= move.toCol)
					//{
					//	return false;
					//}

					if (board[i][move.fromRow]->getPieceType() != PieceType::Empty)
					{
						return false;
					}
				}
				vector<Move> moves = chess.getMoves();
				for (int i = 0; i < moves.size(); i++)
				{
					if (moves.at(i).fromCol == 0 && moves.at(i).fromRow == 7)
					{
						return false;
					}
				}
			}
			// Right rook
			else
			{
				for (int i = move.fromCol; i < 7; i++)
				{
					//if (check(board[i][move.fromRow] && i <= move.toCol)
					//{
					//	return false;
					//}
					if (board[i][move.fromRow]->getPieceType() != PieceType::Empty)
					{
						return false;
					}
				}
				vector<Move> moves = chess.getMoves();
				for (int i = 0; i < moves.size(); i++)
				{
					if (moves.at(i).fromCol == 7 && moves.at(i).fromRow == 7)
					{
						return false;
					}
				}

			}
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

	hasMoved = true;
}
