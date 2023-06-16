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
		else
		{
			saveName = "CANCEL";
		}
	}

	// Load a save file
	else if (choice == 2)
	{
		// Get the name of the existing file (learn how to check if it exists)
		// Call makeMove() until eof
		std::string answer = chessIO::getExistingSaveName();
		if (answer != "CANCEL")
		{
			saveName = answer;

			// Load the saved game
			chessIO::loadSavedGame(chess, saveName);
		}

		// Start over (Might not be the best way to do this)
		else
		{
			playChess();
		}	
	}

	// Flush the buffer
	char temp[1];
	cin.getline(temp, 1);
	while (status == Status::Active)
	{
		// Print the board
		chessIO::printBoard(chess);
		
		// Get and make the move
		chess.makeMove(chessIO::getMove());

		// Save the game if the user chose to saave it
		if (saveName != "CANCEL")
		{
			chessIO::saveGame(chess.getMoves(), saveName);
		}
		
		status = chess.updateStatus();
	}
	return status;

}
int main()
{
	playChess();
	return 0;
}