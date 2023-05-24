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
		board[1][i].pieceType = PieceType::Pawn;
		board[1][i].player = Player::White;

		// Black pawns
		board[6][i].pieceType = PieceType::Pawn;
		board[6][i].player = Player::Black;
	}

	// Place remaining white peices
	// Rooks
	board[0][0].pieceType = PieceType::Rook;;
	board[0][7].pieceType = PieceType::Rook;
	// Knights
	board[0][1].pieceType = PieceType::Knight;
	board[0][6].pieceType = PieceType::Knight;
	// Bishops
	board[0][2].pieceType = PieceType::Bishop;
	board[0][5].pieceType = PieceType::Bishop;
	//Queen
	board[0][3].pieceType = PieceType::Queen;
	//King
	board[0][4].pieceType = PieceType::King;

	// Place the remaining black pieces
	// Rooks
	board[7][0].pieceType = PieceType::Rook;;
	board[7][7].pieceType = PieceType::Rook;
	// Knights
	board[7][1].pieceType = PieceType::Knight;
	board[7][6].pieceType = PieceType::Knight;
	// Bishops
	board[7][2].pieceType = PieceType::Bishop;
	board[7][5].pieceType = PieceType::Bishop;
	//Queen
	board[7][3].pieceType = PieceType::Queen;
	//King
	board[7][4].pieceType = PieceType::King;

	// Initialize the pieces as the correct color
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		board[0][i].player = Player::White;
		board[7][i].player = Player::Black;
		// Initialize empty places
		for (int j = 2; j < 6; j++)
		{
			board[j][i].pieceType = PieceType::Empty;
			board[j][i].player = Player::None;
		}
	}

	// Initialize moved for all spaces as false
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j].moved = false;
		}
	}

	// Set the current player to white
	currentPlayer = Player::White;
}

bool Chess::checkValidMove(const Move& move)
{
	// Check if the space to be moved to is already occupied by the current player's piece
	if (this->board[move.toRow][move.toCol].player == this->currentPlayer)
	{
		return false;
	}

	// Check if the move is out of bounds
	else if (move.toRow > 7 || move.toRow < 0 || move.toCol > 7 || move.toCol < 0)
	{
		return false;
	}

	// Make sure they are actually moving
	else if (move.fromCol == move.toCol && move.toRow == move.fromRow)
	{
		return false;
	}


	// bool checkIfInCheck
	// bool checkIfWouldBeCheck

	PieceType pieceType = board[move.fromRow][move.fromCol].pieceType;

	if (pieceType == PieceType::Pawn)
	{
		return checkValidPawnMove(move);
	}
	else if (pieceType == PieceType::Rook)
	{
		return checkValidRookMove(move);
	}
	else if (pieceType == PieceType::Bishop)
	{
		return checkValidBishopMove(move);
	}
	else if (pieceType == PieceType::Knight)
	{
		return checkValidKnightMove(move);
	}
	else if (pieceType == PieceType::Queen)
	{
		return checkValidQueenMove(move);
	}
	else if (pieceType == PieceType::King)
	{
		return checkValidKingMove(move);
	}

	return false;
}

bool Chess::checkValidPawnMove(const Move& move) const
{
	// Check if the player attempts to make a horizontal move, if capturing correctly, allow, else, block
	if (move.fromRow == move.toRow)
	{
		return false;
	}
	// Check if move is out of bounds or < 1 or > -1 horizontally
	else if (move.fromCol - move.toCol > 1 || move.fromCol - move.toCol < -1)
	{
		return false;
	}

	int maxDistance;
	if (currentPlayer == Player::White)
	{
		// If the player has not moved the pawn yet, allow them to move one or two places, else, allow them to move it only one place
		if (move.fromRow == 2)
		{
			maxDistance = 2;
		}
		else
		{
			maxDistance = 1;
		}
		// Check if the location is invalid
		if ((move.toRow <= move.fromRow) || (maxDistance < (move.toRow - move.fromRow)))
		{
			return false;
		}

		// Only allow horizontal moves if capturing
		else if (move.toCol != move.fromCol && (board[move.toRow][move.toCol].player != Player::Black && (maxDistance == 1 || (maxDistance == 2 && board[move.toRow - 1][move.toCol].player != Player::Black))))
		{
			return false;
		}

		// Check if the location is already occupied if not capturing
		else if (board[move.toRow][move.toCol].player != Player::None && move.toCol == move.fromCol)
		{
			return false;
		}

		// If moving two places, make sure the piece is not moving through another piece
		else if (move.toRow - move.fromRow == 2 && board[move.toRow - 1][move.toCol].player != Player::None)
		{
			return false;
		}

		return true;
	}

	else if (currentPlayer == Player::Black)
	{
		// Allow movements of 1 or 2 places if the pawn has not been moved yet, else, only allow 1
		if (move.fromRow == 7)
		{
			maxDistance = -2;
		}
		else
		{
			maxDistance = -1;
		}

		// Check if the location is invalid
		if ((move.toRow >= move.fromRow) || (maxDistance > (move.toRow - move.fromRow)))
		{

			return false;
		}

		// Check if capturing a piece
		else if (move.toCol != move.fromCol && (board[move.toRow][move.toCol].player != Player::Black && (maxDistance == 1 || (maxDistance == 2 && board[move.toRow + 1][move.toCol].player != Player::White))))
		{
			return false;
		}

		// If not capturing, make sure the location is empty
		else if (board[move.toRow][move.toCol].player != Player::None && move.toCol == move.fromCol)
		{
			return false;
		}

		// If moving two places, make sure the piece is not moving through another piece
		else if (move.fromRow - move.toRow == 2 && board[move.toRow + 1][move.toCol].player != Player::None)
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
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

bool Chess::checkValidKingMove(const Move& move) const
{
	// Does not currently support castling (use moved to determine if the king or rook has been moved)

	// Prevent the king from moving more than one space 
	if (std::abs(move.toCol - move.fromCol) > 1 || std::abs(move.toRow - move.fromRow) > 1)
	{
		return false;
	}

	return true;
}

const Piece& Chess::getBoard(int row, int col) const
{
	return board[row][col];
}
