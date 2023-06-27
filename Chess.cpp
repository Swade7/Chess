#include "ChessIO.hpp"
#include "AI.hpp"

int oneOrTwoPlayer()
{
	cout << endl;
	cout << "Do you want to play a two player game or against the computer?" << endl;
	cout << "Enter 1 to play against the computer. " << endl;
	cout << "Enter 2 to play against another player. " << endl;

	// Get the choice from the user
	int answer;
	bool valid = false;
	cin >> answer;
	if (answer == 1 || answer == 2)
	{
		valid = true;
	}

	// Keep asking for input until the answer is 1 or 2
	while (valid == false)
	{
		cout << endl;
		cout << "Invalid input." << endl;
		cout << "Enter 1 to play against the computer. " << endl;
		cout << "Enter 2 to play against another player. " << endl;

		cin >> answer;
		if (answer == 1 || answer == 2)
		{
			valid = true;
		}
	}
	return answer;
}
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
	// Get the choice for playing against a local opponent of the computer
	int opponentChoice = 0;

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

		opponentChoice = oneOrTwoPlayer();
	}

	// Load a save file
	else if (choice == 2)
	{
		// Get the name of the existing file 
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
		
		// Have the CPU make a move if the user selected to play against the computer and it is black's turn
		if (chess.getCurrentPlayer() == Player::Black && opponentChoice == 1)
		{
			AI::randomMoves(chess);
		}
		else
		{
			// Get and make the move
			chess.makeMove(chessIO::getMove());
		}

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
	Status status;
	status = playChess();
	return 0;
}