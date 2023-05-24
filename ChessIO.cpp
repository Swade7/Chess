#include "ChessIO.hpp"

void chessIO::printBoard(const Chess& chess)
{
	// Output who's turn it is
	if (chess.currentPlayer == Player::White)
	{
		cout << "White's turn" << endl;
	}

	else if (chess.currentPlayer == Player::Black)
	{
		cout << "Black's turn" << endl;
	}


	cout << endl;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << "|";
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			for (int k = 0; k < BOARD_SIZE; k++)
			{
				cout << "--";
			}
			const Piece& piece = chess.getBoard(i, j);

			// Output which player the piece belongs to
			if (piece.player == Player::None)
			{
				cout << " ";
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
				cout << "P";
			}
			else if (piece.pieceType == PieceType::Rook)
			{
				cout << "R";
			}
			else if (piece.pieceType == PieceType::Knight)
			{
				cout << "N";
			}
			else if (piece.pieceType == PieceType::Bishop)
			{
				cout << "B";
			}
			else if (piece.pieceType == PieceType::Queen)
			{
				cout << "Q";
			}
			else if (piece.pieceType == PieceType::King)
			{
				cout << "K";
			}
			cout << "|";

			cout << " ";
			for (int k = 0; k < BOARD_SIZE; k++)
			{
				cout << "--";
			}
		}

		cout << endl;
	}
}
