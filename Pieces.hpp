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
	const Player& getPlayer() const;

	// Setters
	static void addToCapturedPieces(PieceType capturedPiece, Player player);
	static void removeFromPieces(PieceType piece, Player player);

protected:
	virtual bool checkValidMove(const Move& move, const Chess& chess) const = 0;
	virtual void movePiece(const Move& move, Chess& chess) = 0;

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