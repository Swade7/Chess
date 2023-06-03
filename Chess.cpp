//#include "Pieces.hpp"
#include "ChessIO.hpp"

int main()
{
	Chess chess;
	chessIO io;
	io.printBoard(chess);

	Status status = Status::Active;

	while (status == Status::Active)
	{
		Move move = io.getMove();
		chess.makeMove(move);
		io.printBoard(chess);

	}
	return 0;
}