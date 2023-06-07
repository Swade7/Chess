//#include "Pieces.hpp"
#include "ChessIO.hpp"

int main()
{
	Chess chess;
	chessIO io;
	io.printBoard(chess);

	Status status = Status::Active;

	int counter = 0;
	while (counter < 5)
	{
		Move move = io.getMove();
		chess.makeMove(move);
		io.printBoard(chess);
		counter++;
	}
	std::string save = "save.txt";
	io.saveGame(chess, save);
	return 0;
}