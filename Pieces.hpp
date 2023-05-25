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

struct Piece
{
	PieceType pieceType;
	Player player;
	//bool moved;
};

enum class Player : char
{
	White = 'W',
	Black = 'B',
	None = 'N'
};

class Pieces
{
public:
	

	// Getters
	const PieceType& getPieceType(const Chess& board, const Move& move) const;

protected:
	// Constructor
	Pieces(PieceType pieceType, Player player);

	virtual bool checkValidMove(const Move& move, const Chess& board) const = 0;
	virtual void movePiece(const Move& move, Chess& board) = 0;
	void addToCapturedPieces(PieceType capturedPiece, Player player);
	void removeFromPieces(Piece piece, Player player);
	

	

private:
	// Vectors for pieces
	vector<Piece> whitePieces;
	vector<Piece> blackPieces;

	// Vectors for captured pieces
	vector<PieceType> capturedWhitePieces;
	vector<PieceType> capturedBlackPieces;
};