//#include "Pieces.hpp"
#include "ChessIO.hpp"
Status playChess()
{
	// Variable declarations
	std::string saveName;

	// Set the status to active
	Status status = Status::Active;

	// Create a Chess object
	Chess chess;

	// 1 to start a new game, 2 to load an existing game
	int choice = chessIO::startMenu();

	// Create a new game
	if (choice == 1)
	{
		// Check if the user wants to create a new save file
		
		char saveChoice = chessIO::saveChoice();
		if (saveChoice == 'Y')
		{
			saveName = chessIO::createSaveName();
		}		
	}

	// Load a save file
	else if (choice == 2)
	{
		// Get the name of the existing file (learn how to check if it exists)
		// Call makeMove() until eof
		std::string answer = chessIO::getExistingSaveName();
		if (toupper(answer) != "CANCEL")
		{
			saveName = answer;
		}
		

	}

	while (status == Status::Active)
	{
		// Print the board
		chessIO::printBoard(chess);

		// Get and make the move
		chess.makeMove(chessIO::getMove());
	}

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