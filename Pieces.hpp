#pragma once

#include"ChessLogic.hpp"


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
};

class Chess;

class Pieces
{
public:
	// Constructor
	Pieces(PieceType pieceType, Player player);
	
	// Destructor
	virtual ~Pieces();

	// Getters
	virtual const PieceType& getPieceType() const = 0;
	virtual const Player& getPlayer() const = 0;

	// Setters
	static void addToCapturedPieces(PieceType capturedPiece, Player player);
	static void removeFromPieces(PieceType piece, Player player);

	virtual bool checkValidMove(const Move& move, Pieces* board[BOARD_SIZE][BOARD_SIZE], Player currentPlayer, const Move& lastMove) const = 0;
	virtual void updatePiece() = 0;
	

private:
/*	// Vectors for pieces
	static vector<Piece> whitePieces;
	static vector<Piece> blackPieces;

	// Vectors for captured pieces
	static vector<PieceType> capturedWhitePieces;
	static vector<PieceType> capturedBlackPieces;
*/
	// Store the PieceType and Player
	PieceType pieceType;
	Player player;
};