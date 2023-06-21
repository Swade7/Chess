#include "ChessLogic.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "knight.hpp"
#include "Bishop.hpp"
#include "Empty.hpp"
#include "ChessIO.hpp"

// Constructor
Chess::Chess()
{
	initializeBoard();
}

// Copy Constructor
Chess::Chess(Chess& rhs)
{
	// Copy the board
	for (int col = 0; col < BOARD_SIZE; col++) 
	{
		for (int row = 0; row < BOARD_SIZE; row++) 
		{
			board[col][row] = rhs.board[col][row]->clone();
		}
	}

	// Set the variables of the copy to the correct values
	currentPlayer = rhs.currentPlayer;
	hasWhiteCastled = rhs.hasWhiteCastled;
	hasBlackCastled = rhs.hasBlackCastled;
	moveCount = rhs.moveCount;
}

void Chess::initializeBoard()
{
	// Declare the starting rows for the white and black pieces
	//int whiteRow = 0;
	//int blackRow = BOARD_SIZE - 1;

	// Place pawns
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		board[i][WHITE_ROW + 1] = new Pawn(Player::White);
		board[i][BLACK_ROW - 1] = new Pawn(Player::Black);
	}

	// Rooks
	board[0][WHITE_ROW] = new Rook(Player::White);
	board[0][BLACK_ROW] = new Rook(Player::Black);
	board[7][WHITE_ROW] = new Rook(Player::White);
	board[7][BLACK_ROW] = new Rook(Player::Black);
	// Knights
	board[1][WHITE_ROW] = new Knight(Player::White);
	board[1][BLACK_ROW] = new Knight(Player::Black);
	board[6][WHITE_ROW] = new Knight(Player::White);
	board[6][BLACK_ROW] = new Knight(Player::Black);
	// Bishops
	board[2][WHITE_ROW] = new Bishop(Player::White);
	board[2][BLACK_ROW] = new Bishop(Player::Black);
	board[5][WHITE_ROW] = new Bishop(Player::White);
	board[5][BLACK_ROW] = new Bishop(Player::Black);
	//Queen
	board[3][WHITE_ROW] = new Queen(Player::White);
	board[3][BLACK_ROW] = new Queen(Player::Black);
	//King
	board[4][WHITE_ROW] = new King(Player::White);
	board[4][BLACK_ROW] = new King(Player::Black);

	// Add the pieces to the vector of each piece type
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		whitePieces.push_back(board[i][WHITE_ROW]);
		whitePieces.push_back(board[i][WHITE_ROW + 1]);
		blackPieces.push_back(board[i][WHITE_ROW]);
		blackPieces.push_back(board[i][BLACK_ROW - 1]);
	}

	// Initialize the empty places
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		for (int row = WHITE_ROW + 2; row <= BLACK_ROW - 2; row++)
		{
			board[col][row] = new Empty();
		}
	}
	
	// Set the current player to white
	currentPlayer = Player::White;

	moveCount = 0;
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
		if (!wouldBeCheck(move))
		{
			// If castling, move the rook as well
			if (pieceType == PieceType::King && std::abs(move.fromCol - move.toCol) == 2)
			{
				castle(move);
			}
			updateBoard(move);
			piece->updatePiece();
			moves.push_back(move);
			changeTurn();

			Move lastMove = getLastMove();
			std::cout << lastMove.fromCol << ", " << lastMove.fromRow << ", " << lastMove.toCol << ", " << lastMove.toRow << std::endl;
		}
		else
		{
			std::cout << "Would be check" << std::endl;
		}
	}	
	else
	{
		std::cout << "Invalid move." << std::endl;
	}
}

void Chess::castle(const Move& move)
{
	// Get the location of the Rook and move it
	Move rookMove;
	// Set the to and from row based on the player's color
	if (currentPlayer == Player::White)
	{
		rookMove.fromRow = WHITE_ROW;
		rookMove.toRow = WHITE_ROW;
	}
	else if (currentPlayer == Player::Black)
	{
		rookMove.fromRow = BLACK_ROW;
		rookMove.toRow = BLACK_ROW;
	}
	else
	{
		return;
	}
	// Determine if the rook to the left or right should be moved
	// Left
	if (move.fromCol > move.toCol)
	{
		rookMove.fromCol = 0;
		rookMove.toCol = move.toCol + 1;
	}
	// Right
	else if (move.fromCol < move.toCol)
	{
		rookMove.fromCol = BOARD_SIZE - 1;
		rookMove.toCol = move.toCol - 1;
	}
	else
	{
		return;
	}

	// get the Rook at the location
	Rook* rook = dynamic_cast<Rook*>(getPiece(rookMove.fromCol, rookMove.fromRow));

	// Update the piece and the board
	updateBoard(rookMove);
	rook->updatePiece();
}

Status Chess::updateStatus()
{
	if (isStalemate())
	{
		return Status::Stalemate;
	}
	else if (checkmate())
	{
		if (currentPlayer == Player::White)
		{
			return Status::BlackWin;
		}
		else if (currentPlayer == Player::Black)
		{
			return Status::WhiteWin;
		}
	}
	
	return Status::Active;
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
		if (GetPossibleMoves().size() == 0)
		{
			std::cout << "Checkmate" << std::endl;
			return true;
		}
	}

	return false;
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
				if (piece->checkValidMove(move, board, opponent, getLastMove()))
				{
					std::cout << "In check by: ";
					PieceType piecetype = piece->getPieceType();
					std::cout << col << ", " << row << " ";
					if (piecetype == PieceType::Empty)
						std::cout << "Empty";
					else if (piecetype == PieceType::Pawn)
						std::cout << "Pawn";
					else if (piecetype == PieceType::Queen)
						std::cout << "Queen";
					else
						std::cout << "Check!";
					std::cout << std::endl;
					return true;
				}
			}			
		}
	}
	//std::cout << "Not Check" << std::endl;
	return false;
}

bool Chess::isStalemate()
{
	if (!check())
	{
		if (GetPossibleMoves().size() == 0)
		{
			return true;
		}	
	}
	return false;
}

bool Chess::wouldBeCheck(Move move)
{
	// Create a copy of the game to test a move
	Chess chessCopy = *this;

	Pieces* piece = chessCopy.getPiece(move.fromCol, move.fromRow);

	// Update the board	
	chessCopy.updateBoard(move);
	piece->updatePiece();

	// Return if the user would be in check as a result of the move
	return chessCopy.check();
}



// Getters
const vector<Move> Chess::GetPossibleMoves() 
{
	// Create a vector to store the possible moves
	vector<Move> moves;
	// Get that belong to the current player
	vector<Pieces*> pieces;
	if (currentPlayer == Player::White)
	{
		pieces = whitePieces;
	}
	else if (currentPlayer == Player::Black)
	{
		pieces = blackPieces;
	}

	int piecesChecked = 0;
	// Iterate over the board to find the pieces that belong to the currentPlayer
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		for (int row = 0; row < BOARD_SIZE; row++)
		{
			if (board[col][row]->getPlayer() == currentPlayer)
			{
				Pieces* currentPiece = getPiece(col, row);
				// Check each possible to location
				for (int toCol = 0; toCol < BOARD_SIZE; toCol++)
				{
					for (int toRow = 0; toRow < BOARD_SIZE; toRow++)
					{
						Move move = { col, row, toCol , toRow };
						if (board[row][col]->checkValidMove(move, board, currentPlayer, getLastMove()))
						{
							moves.push_back(move);
							piecesChecked++;

							if (piecesChecked >= pieces.size())
							{
								return moves;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < moves.size(); i++)
	{
		Pieces* piece = getPiece(moves.at(i).fromCol, moves.at(i).fromRow);
		if (piece->getPieceType() == PieceType::Queen)
		{
			std::cout << moves.at(i).fromCol << ", " << moves.at(i).fromRow << std::endl;
		}
		else
		{
			std::cout << "Not Queen" << moves.at(i).fromCol << ", " << moves.at(i).fromRow << std::endl;;
		}
	}
	return moves;
}

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