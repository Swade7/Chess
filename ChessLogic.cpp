#include "ChessLogic.hpp"


Chess::Chess()
{
	initializeBoard();
}

void Chess::initializeBoard()
{
	// Place pawns
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		// White pawns
		board[i][1].pieceType = PieceType::Pawn;
		board[i][1].player = Player::White;

		// Black pawns
		board[i][6].pieceType = PieceType::Pawn;
		board[i][6].player = Player::Black;
	}

	// Place remaining white peices
	// Rooks
	board[0][0].pieceType = PieceType::Rook;;
	board[7][0].pieceType = PieceType::Rook;
	// Knights
	board[1][0].pieceType = PieceType::Knight;
	board[6][0].pieceType = PieceType::Knight;
	// Bishops
	board[2][0].pieceType = PieceType::Bishop;
	board[5][0].pieceType = PieceType::Bishop;
	//Queen
	board[3][0].pieceType = PieceType::Queen;
	//King
	board[4][0].pieceType = PieceType::King;

	// Place the remaining black pieces
	// Rooks
	board[0][7].pieceType = PieceType::Rook;;
	board[7][7].pieceType = PieceType::Rook;
	// Knights
	board[1][7].pieceType = PieceType::Knight;
	board[6][7].pieceType = PieceType::Knight;
	// Bishops
	board[2][7].pieceType = PieceType::Bishop;
	board[5][7].pieceType = PieceType::Bishop;
	//Queen
	board[3][7].pieceType = PieceType::Queen;
	//King
	board[4][7].pieceType = PieceType::King;

	// Initialize the pieces as the correct color
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		board[i][0].player = Player::White;
		board[i][7].player = Player::Black;
		// Initialize empty places
		for (int j = 2; j < 6; j++)
		{
			board[i][j].pieceType = PieceType::Empty;
			board[i][j].player = Player::None;
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

const Piece(&Chess::getBoard() const)[BOARD_SIZE][BOARD_SIZE]
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




