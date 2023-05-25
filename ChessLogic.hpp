#pragma once

#include<string>
#pragma once

#include "Pieces.hpp"
#include<vector>
#include "Pieces.hpp"
using std::vector;





enum class Player : char
{
	White = 'W',
	Black = 'B',
	None = 'N'
};

struct Move {
	int fromRow;
	int fromCol;
	int toRow;
	int toCol;
};

const int BOARD_SIZE = 8;

class Chess
{
public:
	//Constructor
	Chess();

	Move GetPossibleMoves();

	// Getters
	const Player& getCurrentPlayer() const;
	const Piece& getBoard(const int row, const int col) const;
	

	


private:
	// Function Definitions
	void initializeBoard();

	// Functions to check if a move is valid
	
	bool checkValidPawnMove(const Move& move) const;
	bool checkValidKnightMove(const Move& move) const;
	bool checkValidBishopMove(const Move& move) const;
	bool checkValidRookMove(const Move& move) const;
	bool checkValidQueenMove(const Move& move) const;
	bool checkValidKingMove(const Move& move) const;
	bool canCastle(const Move& move) const;

	

	


	// Declare the board using a 2D array of type Piece(char)
	Piece board[BOARD_SIZE][BOARD_SIZE];



	// Keep track of the current player's turn
	Player currentPlayer;

	// Keep track of if each player has castled
	bool hasWhiteCastled = false;
	bool hasBlackCastled = false;

};