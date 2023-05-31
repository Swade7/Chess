#pragma once

#include "Pieces.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "knight.hpp"
#include "Bishop.hpp"
#include "Empty.hpp"
#include<string>
#include<vector>

using std::vector;


enum class Status
{
	Active,
	WhiteWin,
	BlackWin,
	Stalemate,
	GameOver
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

	const vector<Move> GetPossibleMoves() const;

	// Getters
	const Player& getCurrentPlayer() const;
	const Pieces* const (&getBoard() const)[BOARD_SIZE][BOARD_SIZE];
	const vector<Move> getMoves() const;
	const Move& getLastMove() const;
	const int getNumMoves() const;

	// Setters
	void changeTurn();
	void updateBoard(const Move& move);
	void addMove(const Move& move);

	// Checks for check/checkmate/stalemate
	bool checkmate();
	bool check(Piece piece, int col, int row);
	bool isStalemate();


private:
	// Function Definitions
	void initializeBoard();

	// Declare the board using a 2D array of the Pieces class
	Pieces* board[BOARD_SIZE][BOARD_SIZE];

	// Keep track of the current player's turn
	Player currentPlayer = Player::White;

	// Keep track of if each player has castled
	bool hasWhiteCastled = false;
	bool hasBlackCastled = false;

	// Keep track of the number of moves
	int moveCount;

	// Keep track of the moves
	vector<Move> moves;


};