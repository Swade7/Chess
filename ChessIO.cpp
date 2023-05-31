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
	Player currentPlayer = chess.getCurrentPlayer();
	cout << currentPlayer << "'s turn";
	cout << endl << " ";

	for (int col = 0; col < BOARD_SIZE * 4 + 1; col++)
	{
		cout << "_";
	}
	cout << endl;

	// Get the board
	const Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		cout << "| ";
		for (int col = 0; col < BOARD_SIZE; col++)
		{	
			PieceType pieceType = board[col][row]->getPieceType();
			Player player = board[col][row]->getPlayer();

			// Output which player the piece belongs to at the location
			if (player == Player::None)
			{
				cout << "+ ";
			}
			else if (player == Player::White)
			{
				cout << "W";
			}
			else if (player == Player::Black)
			{
				cout << "B";
			}

			// Output what type of piece is at the location
			if (pieceType == PieceType::Empty)
			{
				cout << " ";
			}
			else if (pieceType == PieceType::Pawn)
			{
				cout << "P ";
			}
			else if (pieceType == PieceType::Rook)
			{
				cout << "R ";
			}
			else if (pieceType == PieceType::Knight)
			{
				cout << "N ";
			}
			else if (pieceType == PieceType::Bishop)
			{
				cout << "B ";
			}
			else if (pieceType == PieceType::Queen)
			{
				cout << "Q ";
			}
			else if (pieceType == PieceType::King)
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
	// Get the board
	const Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

	Player player = board[move.toCol][move.toRow]->getPlayer();

	cout << player << " Moved their " << board[move.toCol][move.toRow]->getPieceType() << " from "  << intToChar(move.fromCol) << move.fromRow << " to " << intToChar(move.toCol) << move.toRow << endl;
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

const int chessIO::charToInt(char& c)
{
	c = toupper(c);
	if (c == 'A')
	{
		return 0;
	}
	else if (c == 'B')
	{
		return 1;
	}
	else if (c == 'C')
	{
		return 2;
	}
	else if (c == 'D')
	{
		return 3;
	}
	else if (c == 'E')
	{
		return 4;
	}
	else if (c == 'F')
	{
		return 5;
	}
	else if (c == 'G')
	{
		return 6;
	}
	else if (c == 'H')
	{
		return 7;
	}
}

Move chessIO::getMove()
{
	char from[2];
	char to[2];
	// Get the from and to locations from the user
	cout << "Enter the piece you would like to move: ";
	cin.getline(from, 2);
	cout << endl;
	cout << "Enter the destination location: ";
	cin.getline(to, 2);
	cout << endl;

	// TO DO -- Add data validation checks

	Move move;
	move.fromCol = charToInt(from[0]);
	move.fromRow = int(from[1] + 1);
	move.toCol = charToInt(to[0]);
	move.toRow = int(to[1] + 1);

	if (inRange(move.fromCol, move.toCol) && inRange(move.toCol, move.fromCol))
	{
		return move;
	}
	else
	{
		// Print invalid input
		getMove();
	}
}

bool chessIO::inRange(int a, int b)
{
	if (a > BOARD_SIZE || a < 1 || b > BOARD_SIZE || b < 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}


