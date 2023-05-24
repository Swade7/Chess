#include "ChessIO.hpp"


std::ostream& operator<<(std::ostream& out, Player const& player)
{
	if (player == Player::White)
	{
		return out << "White";
	}
	else if (player == Player::Black)
	{
		return out << "Black";
	}
	else
	{
		return out << "Error, player not found.";
	}
}

std::ostream& operator<<(std::ostream& out, PieceType const& pieceType)
{
	if (pieceType == PieceType::Pawn)
	{
		return out << "Pawn";
	}
	if (pieceType == PieceType::Rook)
	{
		return out << "Rook";
	}
	if (pieceType == PieceType::Knight)
	{
		return out << "Knight";
	}
	if (pieceType == PieceType::Bishop)
	{
		return out << "Bishop";
	}
	if (pieceType == PieceType::Queen)
	{
		return out << "Queen";
	}
	if (pieceType == PieceType::King)
	{
		return out << "King";
	}
	else
	{
		return out << "Invalid piece";
	}
}

void chessIO::printBoard(const Chess& chess)
{
	Player p = chess.getCurrentPlayer();
	cout << p << "'s turn";
	cout << endl << " ";

	for (int col = 0; col < BOARD_SIZE * 4 + 1; col++)
	{
		cout << "_";
	}

	cout << endl;
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		cout << "| ";
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			
			const Piece& piece = chess.getBoard(col, row);

			// Output which player the piece belongs to
			if (piece.player == Player::None)
			{
				cout << "+ ";
			}
			else if (piece.player == Player::White)
			{
				cout << "W";
			}
			else if (piece.player == Player::Black)
			{
				cout << "B";
			}

			if (piece.pieceType == PieceType::Empty)
			{
				cout << " ";
			}
			else if (piece.pieceType == PieceType::Pawn)
			{
				cout << "P ";
			}
			else if (piece.pieceType == PieceType::Rook)
			{
				cout << "R ";
			}
			else if (piece.pieceType == PieceType::Knight)
			{
				cout << "N ";
			}
			else if (piece.pieceType == PieceType::Bishop)
			{
				cout << "B ";
			}
			else if (piece.pieceType == PieceType::Queen)
			{
				cout << "Q ";
			}
			else if (piece.pieceType == PieceType::King)
			{
				cout << "K ";
			}
			
			cout << " ";
		}
		cout << "|";
		if (row < 7)
		{
			cout << endl << endl;
		}
		
	}
	cout << endl << " ";
	for (int col = 0; col < BOARD_SIZE * 4 + 1; col++)
	{
		cout << "-";
	}
	
	cout << endl << endl << endl << endl;
}

void chessIO::printMove(const Chess& chess, const Move& move)
{
	Player p = chess.getCurrentPlayer();

	cout << p << " Moved their " << chess.getPieceType(move) << " from "  << intToChar(move.fromCol) << move.fromRow << " to " << intToChar(move.toCol) << move.toRow << endl;
}

void chessIO::printInvalidMove(std::ostream& out)
{
	out << "Invalid move" << endl;
}

const char chessIO::intToChar(const int& i)
{
	if (i == 0)
	{
		return 'A';
	}
	else if (i == 1)
	{
		return 'B';
	}
	else if (i == 2)
	{
		return 'C';
	}
	else if (i == 3)
	{
		return 'D';
	}
	else if (i == 4)
	{
		return 'E';
	}
	else if (i == 5)
	{
		return 'F';
	}
	else if (i == 6)
	{
		return 'G';
	}
	else if (i == 7)
	{
		return 'H';
	}
}


