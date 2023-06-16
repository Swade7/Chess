#pragma once

#include<string>
#include<vector>
#include<iostream>

using std::vector;

enum class PieceType : char;

enum class Player : char;

struct Piece;

class Pieces;


enum class Status
{
	Active,
	WhiteWin,
	BlackWin,
	Stalemate,
	GameOver
};

struct Move {
	int fromCol;
	int fromRow;
	int toCol;
	int toRow;
};

const int BOARD_SIZE = 8;

class Chess
{
public:
	//Constructors
	Chess();
	const Chess(Chess& rhs);

	const vector<Move> GetPossibleMoves();

	// Getters
	const Player& getCurrentPlayer() const;
	const Player& getOpponent() const;
	Pieces* const (&getBoard() const)[BOARD_SIZE][BOARD_SIZE];
	const vector<Move> getMoves() const;
	const Move& getLastMove() const;
	const int getNumMoves() const;
	Pieces* getPiece(int col, int row);

	// Setters
	void changeTurn();
	void updateBoard(const Move& move);
	void makeMove(const Move& move);
	Status updateStatus();

	// Checks for check/checkmate/stalemate
	bool checkmate();
	bool check();
	bool isStalemate();
	bool wouldBeCheck(Move move);


private:
	// Function Definitions
	void initializeBoard();

	// Declare the board using a 2D array of the Pieces class
	Pieces* board[BOARD_SIZE][BOARD_SIZE];

	// Keep track of the current player's turn
	Player currentPlayer;

	// Keep track of if each player has castled
	bool hasWhiteCastled = false;
	bool hasBlackCastled = false;

	// Keep track of the number of moves
	int moveCount;

	// Keep track of the moves
	vector<Move> moves;

	// Keep track of the pieces for each color
	vector<Pieces*> whitePieces;
	vector<Pieces*> blackPieces;
};