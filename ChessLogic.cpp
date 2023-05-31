#include "ChessLogic.hpp"


Chess::Chess()
{
	initializeBoard();
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

	// Initialize the empty places
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		for (int row = whiteRow + 2; row < blackRow - 2; row++)
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
		currentPlayer == Player::Black;
	}
	else if (currentPlayer == Player::Black)
	{
		currentPlayer = Player::White;
	}
}

void Chess::updateBoard(const Move& move)
{
	// If a piece is captured, add it to the capturedPieces vector and remove it from the appropriate pieces vector
	if (board[move.toCol][move.toRow].pieceType != PieceType::Empty)
	{
		Pieces::addToCapturedPieces(board[move.toCol][move.toRow].pieceType, board[move.toCol][move.toRow].player);
		Pieces::removeFromPieces(board[move.toCol][move.toRow].pieceType, board[move.toCol][move.toRow].player);
	}
	

	// Set the to location equal to the from location
	board[move.toCol][move.toRow] = board[move.fromCol][move.fromRow];
	board[move.fromCol][move.fromRow].pieceType = PieceType::Empty;
	board[move.fromCol][move.fromRow].player = Player::None;
}

void Chess::addMove(const Move& move)
{
	moves.push_back(move);
}

// Getters

const Player& Chess::getCurrentPlayer() const
{
	return currentPlayer;
}

const Pieces* const (&Chess::getBoard() const)[BOARD_SIZE][BOARD_SIZE]
{
	return board;
}

const vector<Move> Chess::getMoves() const
{
	return moves;
}

const Move& Chess::getLastMove() const
{
	return moves.at(moves.size() - 1);
}

const int Chess::getNumMoves() const
{
	return moves.size();
}




