#include "ChessLogic.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "knight.hpp"
#include "Bishop.hpp"
#include "Empty.hpp"


Chess::Chess()
{
	initializeBoard();
}

const vector<Move> Chess::GetPossibleMoves() const
{
	vector<Move> moves;

	return moves;
}

void Chess::initializeBoard()
{
	// Declare the starting rows for the white and black pieces
	int whiteRow = 0;
	int blackRow = BOARD_SIZE - 1;

	// Place pawns
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		board[i][whiteRow + 1] = new Pawn(Player::White);
		board[i][blackRow - 1] = new Pawn(Player::Black);
	}

	// Rooks
	board[0][whiteRow] = new Rook(Player::White);
	board[0][blackRow] = new Rook(Player::Black);
	board[7][whiteRow] = new Rook(Player::White);
	board[7][blackRow] = new Rook(Player::Black);
	// Knights
	board[1][whiteRow] = new Knight(Player::White);
	board[1][blackRow] = new Knight(Player::Black);
	board[6][whiteRow] = new Knight(Player::White);
	board[6][blackRow] = new Knight(Player::Black);
	// Bishops
	board[2][whiteRow] = new Bishop(Player::White);
	board[2][blackRow] = new Bishop(Player::Black);
	board[5][whiteRow] = new Bishop(Player::White);
	board[5][blackRow] = new Bishop(Player::Black);
	//Queen
	board[3][whiteRow] = new Queen(Player::White);
	board[3][blackRow] = new Queen(Player::Black);
	//King
	board[4][whiteRow] = new King(Player::White);
	board[4][blackRow] = new King(Player::Black);

	// Add the pieces to the vector of each piece type
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		whitePieces.push_back(board[i][whiteRow]);
		whitePieces.push_back(board[i][whiteRow + 1]);
		blackPieces.push_back(board[i][blackRow]);
		blackPieces.push_back(board[i][blackRow - 1]);
	}

	// Initialize the empty places
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		for (int row = whiteRow + 2; row <= blackRow - 2; row++)
		{
			board[col][row] = new Empty();
		}
	}
	
	// Set the current player to white
	currentPlayer = Player::White;
}

// Setters
void Chess::changeTurn()
{
	if (currentPlayer == Player::White)
	{
		currentPlayer = Player::Black;
	}
	else if (currentPlayer == Player::Black)
	{
		currentPlayer = Player::White;
	}
}

void Chess::updateBoard(const Move& move)
{
	// If a piece is captured, add it to the capturedPieces vector and remove it from the appropriate pieces vector
	if (board[move.toCol][move.toRow]->getPieceType() != PieceType::Empty)
	{
		//Pieces::addToCapturedPieces(board[move.toCol][move.toRow]->getPieceType(), board[move.toCol][move.toRow]->getPlayer());
		//Pieces::removeFromPieces(board[move.toCol][move.toRow]->getPieceType(), board[move.toCol][move.toRow]->getPlayer());
	}
	
	// Delete the piece that used to occupy the location
	Pieces* toDelete = board[move.toCol][move.toRow];
	delete toDelete;

	// Set the to location equal to the from location
	board[move.toCol][move.toRow] = board[move.fromCol][move.fromRow];

	// Create an empty piece where the piece used to be
	board[move.fromCol][move.fromRow] = new Empty();
	if (board[move.fromCol][move.fromRow]->getPlayer() == Player::White)
	{
		std::cout << "Piece is still white" << std::endl;
	}
	if (board[move.fromCol][move.fromRow]->getPieceType() != PieceType::Empty)
		std::cout << "The PieceType is not empty" << std::endl;
}

void Chess::makeMove(const Move& move)
{
	Pieces* piece = getPiece(move.fromCol, move.fromRow);
	PieceType pieceType = piece->getPieceType();

	if (piece->checkValidMove(move, board, currentPlayer, getLastMove()))
	{
		updateBoard(move);
		piece->updatePiece();
		moves.push_back(move);
		changeTurn();

		Move lastMove = getLastMove();
		std::cout << lastMove.fromCol << ", " << lastMove.fromRow << ", " << lastMove.toCol << ", " << lastMove.toRow << std::endl;
	}	
	else
	{
		std::cout << "Invalid move." << std::endl;
	}
}

bool Chess::checkmate()
{
	if (check())
	{
		// Get the king's location
		int kingCol = -1;
		int kingRow = -1;

		for (int col = 0; col < BOARD_SIZE; col++)
		{
			for (int row = 0; row < BOARD_SIZE; row++)
			{
				// Get the piece at the location
				Pieces* piece = getPiece(col, row);
				if (piece->getPieceType() == PieceType::King && piece->getPlayer() == currentPlayer)
				{
					kingCol = col;
					kingRow = row;

					break;
				}
			}
			if (kingCol != -1 && kingRow != -1)
			{
				break;
			}
		}

		// Check if there are any possible moves that would put the player no longer in check
		vector <Move> moves = GetPossibleMoves();
		if (moves.size() > 0)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Chess::check()
{
	// Declare variables for the king location
	int kingCol = -1;
	int kingRow = -1;

	// Get the opponent
	Player opponent = getOpponent();

	// Locate the king
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		for (int row = 0; row < BOARD_SIZE; row++)
		{
			// Get the piece at the location
			Pieces* piece = getPiece(col, row);
			if (piece->getPieceType() == PieceType::King && piece->getPlayer() == currentPlayer)
			{
				kingCol = col;
				kingRow = row;

				break;
			}
		}
		if (kingCol != -1 && kingRow != -1)
		{
			break;
		}
	}

	// Iterate through the rest of the board and check if the king is in check
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		for (int row = 0; row < BOARD_SIZE; row++)
		{
			// Get the piece at the location
			Pieces* piece = getPiece(col, row);

			if (piece->getPlayer() == opponent)
			{
				// Create a Move variable for formatting
				Move move = { col, row, kingCol, kingRow };
				if (piece->checkValidMove(move, board, currentPlayer, getLastMove()))
				{
					return true;
				}
			}
			
		}
	}

	return false;
}
/*
bool Chess::isStalemate()
{
	if (!check())
	{

	}
	return false;
}
*/


// Getters
const Player& Chess::getCurrentPlayer() const
{
	return currentPlayer;
}

const Player& Chess::getOpponent() const
{
	if (currentPlayer == Player::White)
	{
		return Player::Black;
	}
	else if (currentPlayer == Player::Black)
	{
		return Player::White;
	}
	else
	{
		return Player::None;
	}
}

Pieces* const (&Chess::getBoard() const)[BOARD_SIZE][BOARD_SIZE]
{
	return board;
}

const vector<Move> Chess::getMoves() const
{
	return moves;
}

const Move& Chess::getLastMove() const
{
	if (getNumMoves() > 0)
	{
		return moves.at(moves.size() - 1);
	}
	else
	{
		Move temp = { -1, -1, -1, -1 };
		return temp;
	}
}

const int Chess::getNumMoves() const
{
	return moves.size();
}

Pieces* Chess::getPiece(int col, int row)
{
	return board[col][row];
}