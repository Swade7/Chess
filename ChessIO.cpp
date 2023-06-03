#include "ChessIO.hpp"
#include<cstdlib>


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
	Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

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
	Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

	Player player = board[move.toCol][move.toRow]->getPlayer();

	cout << player << " Moved their " << board[move.toCol][move.toRow]->getPieceType() << " from "  << intToChar(move.fromCol) << move.fromRow << " to " << intToChar(move.toCol) << move.toRow << endl;
}

void chessIO::printInvalidMove(std::ostream& out)
{
	out << "Invalid move" << endl;
}

const char chessIO::intToChar(const int& i)
{
	char c = static_cast<char>(i);
	return('A' + c);
}

const int chessIO::charToInt(const char& c)
{
	char upper = toupper(c);
	return upper - 'A';
}

Move chessIO::getMove()
{
	char from[3];
	char to[3];
	// Get the from and to locations from the user
	cout << "Enter the piece you would like to move: ";
	cin.getline(from, 3);
	cout << endl;
	cout << "Enter the destination location: ";
	cin.getline(to, 3);
	cout << endl;

	// TO DO -- Add data validation checks

	Move move;
	move.fromCol = charToInt(from[0]);
	move.fromRow = atoi(std::string(1, from[1]).c_str()) - 1;
	move.toCol = charToInt(to[0]);
	move.toRow = atoi(std::string(1, to[1]).c_str()) - 1;

	cout << move.fromCol  << " " << move.fromRow << " " << move.toCol << " " << move.toRow << " " << endl;

	if (inRange(move.fromCol, move.fromRow) && inRange(move.toCol, move.toRow))
	{
		return move;
	}
	else
	{
		// Print invalid input
		cout << "Error";
	}
}

bool chessIO::inRange(int a, int b)
{
	if (a > BOARD_SIZE || a < 0 || b > BOARD_SIZE || b < 0)
	{
		cout << "Out of range" << endl;
		return false;		
	}
	else
	{
		return true;
	}
}