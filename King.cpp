#include "King.hpp"

#include"Rook.hpp"

// Constructor
King::King(Player player)
	: Pieces(PieceType::King, player)
{
	this->player = player;
	hasMoved = false;
}

// Destructor
King::~King() = default;

// Copy
King* King::clone() const
{
	return new King(*this);
}

// Getters
const PieceType& King::getPieceType() const
{
	return PieceType::King;
}

const Player& King::getPlayer() const
{
	return player;
}

bool King::checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const
{
	// Check if the move is out of bounds
	if (move.toRow > BOARD_SIZE - 1 || move.toRow < 0 || move.toCol > BOARD_SIZE - 1 || move.toCol < 0)
	{
		return false;
	}

	// Check if the piece belongs to the current player
	if (board[move.fromCol][move.fromRow]->getPlayer() != currentPlayer)
	{
		return false;
	}

	// Check if the space to be moved to is already occupied by the current player's piece
	if (board[move.toCol][move.toRow]->getPlayer() == currentPlayer)
	{
		return false;
	}

	// Make sure they are actually moving
	else if (move.fromCol == move.toCol && move.toRow == move.fromRow)
	{
		return false;
	}

	// King specific checks
	// Check if trying to castle
	if (!hasMoved && std::abs(move.fromCol - move.toCol) == 2 && move.fromRow == move.toRow)
	{

		// Get the col of the rook
		int rookCol;
		// Moving right
		if (move.fromCol > move.toCol)
		{
			rookCol = 0;
		}
		// Moving left
		else if (move.fromCol < move.toCol)
		{
			rookCol = 7;
		}
		else
		{
			return false;
		}

		// Get the Row of the rook
		int rookRow;
		// White
		if (board[move.fromCol][move.fromRow]->getPlayer() == Player::White)
		{
			rookRow = 0;
		}
		// Black
		else if (board[move.fromCol][move.fromRow]->getPlayer() == Player::Black)
		{
			rookRow = 7;
		}
		else
		{
			return false;
		}

		// Check if the rook has been moved
		if (board[rookCol][rookRow]->getPieceType() != PieceType::Rook)
		{
			std::cout << "The rook location does not contain the rook" << std::endl;
			return false;
		}
		else
		{
			const Rook* rook = dynamic_cast<const Rook*>(board[rookCol][rookRow]);
			if (rook->getHasMoved())
			{
				std::cout << "The rook has been moved" << std::endl;
				return false;
			}
		}

		// Check if all spaces between the two pieces are empty
		for (int i = std::min(move.fromCol, rookCol) + 1; i < std::max(move.fromCol, rookCol); i++)
		{
			if (board[i][rookRow]->getPieceType() != PieceType::Empty)
			{
				std::cout << "A space between the two pieces is occupied" << std::endl;
				return false;
			}
		}
	}
	else
	{
		// Prevent the king from moving more than one space 
		if (std::abs(move.toCol - move.fromCol) > 1 || std::abs(move.toRow - move.fromRow) > 1)
		{
			std::cout << "The king is being attempted to moved more than one space" << std::endl;
			return false;
		}
	}
	
	
	return true;
}

void King::updatePiece()
{

	// Need to also move the rook if castling
	// Set the hasMoved variable to true
	hasMoved = true;
}

