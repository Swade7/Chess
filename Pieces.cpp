#include "Pieces.hpp"
#include "ChessLogic.hpp"

Pieces::Pieces(PieceType pieceType, Player player)
{
    
}

Pieces::~Pieces()
{
}


const PieceType& Pieces::getPieceType(const Chess& chess, const Move& move) const
{
    const Piece(&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();
    return board[move.toRow][move.toCol].pieceType;
}

void Pieces::addToCapturedPieces(PieceType capturedPiece, Player player)
{
    // White
    if (player == Player::White)
    {
        capturedWhitePieces.push_back(capturedPiece);
    }
    // Black
    else if (player == Player::Black)
    {
        capturedBlackPieces.push_back(capturedPiece);
    }
}

void Pieces::removeFromPieces(PieceType piece, Player player)
{
    // White
    if (player == Player::White)
    {
        for (int i = 0; i < whitePieces.size(); i++)
        {
            if (whitePieces.at(i).pieceType == piece)
            {
                whitePieces.erase(whitePieces.begin() + i);
                return;
            }
        }
    }
    // Black
    else if (player == Player::Black)
    {
        for (int i = 0; i < blackPieces.size(); i++)
        {
            if (blackPieces.at(i).pieceType == piece)
            {
                blackPieces.erase(blackPieces.begin() + i);
                return;
            }
        }
    }
}


