//#include "Pieces.hpp"
#include "ChessIO.hpp"
Status playChess()
{
	// Set the status to active
	Status status = Status::Active;

	// Create a Chess object
	Chess chess;

	// 1 to start a new game, 2 to load an existing game
	int choice = chessIO::startMenu();

	if ()

}
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