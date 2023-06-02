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
		chess.makeMove(move);
		//status = Status::BlackWin;
		io.printBoard(chess);

	}
	return 0;
}