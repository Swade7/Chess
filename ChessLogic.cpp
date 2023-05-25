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



bool Chess::checkValidKnightMove(const Move& move) const
{
	int rowDifference = std::abs(move.toRow - move.fromRow);
	int colDifference = std::abs(move.toCol - move.fromCol);

	if (rowDifference == 1 && colDifference == 2 || colDifference == 1 && rowDifference == 2)
	{
		return true;
	}

	return false;
}

bool Chess::checkValidBishopMove(const Move& move) const
{
	int rowDifference = std::abs(move.toRow - move.fromRow);
	int colDifference = std::abs(move.toCol - move.fromCol);

	if (rowDifference != colDifference)
	{
		return false;
	}

	// Check for pieces blocking the path
	if (move.toCol > move.fromCol)
	{
		if (move.toRow > move.fromRow)
		{
			for (int i = move.fromRow + 1; i < move.toRow; i++)
			{
				if (board[i][move.fromCol + (i - move.fromRow)].player != Player::None)
				{
					return false;
				}
			}
		}
		else
		{
			for (int i = move.fromRow - 1; i > move.toRow; i--)
			{
				if (board[i][move.fromCol + (i - move.fromRow)].player != Player::None)
				{
					return false;
				}
			}
		}
	}
	else
	{
		if (move.toRow > move.fromRow)
		{
			for (int i = move.fromRow + 1; i < move.toRow; i++)
			{
				if (board[i][move.fromCol - (i - move.fromRow)].player != Player::None)
				{
					return false;
				}
			}
		}
		else
		{
			for (int i = move.fromRow - 1; i > move.toRow; i--)
			{
				if (board[i][move.fromCol - (i - move.fromRow)].player != Player::None)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Chess::checkValidRookMove(const Move& move) const
{
	// Check if trying to move diagonally
	if (move.toCol != move.fromCol && move.toRow != move.fromRow)
	{
		return false;
	}

	// Determine if moving vertically or horizontally
	char dir;
	if (move.fromCol == move.toCol)
	{
		dir = 'v';
	}
	else
	{
		dir = 'h';
	}
	// Check if another piece is blocking the path
	// Checks for vertical movements
	if (dir == 'v')
	{
		// Right
		if (move.toRow > move.fromRow)
		{
			for (int i = move.fromRow; i < move.toRow; i++)
			{
				if (board[i][move.fromCol].player != Player::None)
				{
					return false;
				}
			}
		}
		// Left
		else if (move.toRow < move.fromRow)
		{
			for (int i = move.toRow; i < move.fromRow; i++)
			{
				if (board[i][move.fromCol].player != Player::None)
				{
					return false;
				}
			}
		}
	}
	// Checks for horizontal movements
	else if (dir == 'h')
	{
		// Right
		if (move.toCol > move.fromCol)
		{
			for (int i = move.fromCol; i < move.toCol; i++)
			{
				if (board[move.fromRow][i].player != Player::None)
				{
					return false;
				}
			}
		}
		// Left
		else if (move.toCol < move.fromCol)
		{
			for (int i = move.toCol; i < move.fromCol; i++)
			{
				if (board[move.fromRow][i].player != Player::None)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Chess::checkValidQueenMove(const Move& move) const
{
	// Check if the move is valid if moving vertical or horizontal
	if (checkValidRookMove(move) == true)
	{
		return true;
	}

	// Check if the move is valid if moving diagonal
	else if (checkValidBishopMove(move) == true)
	{
		return true;
	}

	return false;
}




// Setters
void Chess::movePiece(const Move& move)
{
	if (checkValidMove(move))
	{
		// If a piece is captured, add it to the correct vector
		if (board[move.toCol][move.toRow].player == Player::White)
		{
			capturedWhitePieces.push_back(board[move.toCol][move.toRow].pieceType);
		}
		else if (board[move.toCol][move.toRow].player == Player::Black)
		{
			capturedBlackPieces.push_back(board[move.toCol][move.toRow].pieceType);
		}

		// Update the board
		board[move.toCol][move.toRow].moved = true;
		board[move.toCol][move.toRow].pieceType = board[move.fromCol][move.fromRow].pieceType;
		board[move.toCol][move.toRow].player = board[move.fromCol][move.fromRow].player;
		board[move.fromCol][move.fromRow].moved = true;

		// set currentPlayer to the opponent
		if (currentPlayer == Player::White)
		{
			currentPlayer == Player::Black;
		}
		else
		{
			currentPlayer = Player::White;
		}
	}
}

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




