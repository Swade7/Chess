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
		//chess.(move);
		chess.addMove(move);
		status = Status::BlackWin;

	}
	return 0;
}