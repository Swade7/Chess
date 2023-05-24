#pragma once

#include<string>
#include<vector>
using std::vector;

enum class PieceType : char
{
	Empty = '+',
	Pawn = 'P',
	Knight = 'N',
	Bishop = 'B',
	Rook = 'R',
	Queen = 'Q',
	King = 'K'
};

enum class Player : char
{
	White = 'W',
	Black = 'B',
	None = 'N'
};

struct Piece
{
	PieceType pieceType;
	Player player;
	bool moved;
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
	const PieceType& getPieceType(const Move& move) const;

	


private:
	// Function Definitions
	void initializeBoard();

	// Functions to check if a move is valid
	bool checkValidMove(const Move& move);
	bool checkValidPawnMove(const Move& move) const;
	bool checkValidKnightMove(const Move& move) const;
	bool checkValidBishopMove(const Move& move) const;
	bool checkValidRookMove(const Move& move) const;
	bool checkValidQueenMove(const Move& move) const;
	bool checkValidKingMove(const Move& move) const;
	bool canCastle(const Move& move) const;

	void movePiece(const Move& move);

	// Checks for check/checkmate/stalemate
	bool checkmate();
	bool check();
	bool isStalemate();


	// Declare the board using a 2D array of type Piece(char)
	Piece board[BOARD_SIZE][BOARD_SIZE];

	// Vectors for pieces
	vector<Piece> whitePieces;
	vector<Piece> blackPieces;

	// Vectors for captured pieces
	vector<PieceType> capturedWhitePieces;
	vector<PieceType> capturedBlackPieces;

	// Keep track of the current player's turn
	Player currentPlayer;

	// Keep track of if each player has castled
	bool hasWhiteCastled = false;
	bool hasBlackCastled = false;

};