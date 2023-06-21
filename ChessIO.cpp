#include "ChessIO.hpp"


std::ostream& operator<<(std::ostream& out, Player const& player)
{
	if (player == Player::White)
	{
		return out << "White";
	}
	else if (player == Player::Black)
	{
		return out << "Black";
	}
	else
	{
		return out << "Error, player not found.";
	}
}

std::ostream& operator<<(std::ostream& out, PieceType const& pieceType)
{
	if (pieceType == PieceType::Pawn)
	{
		return out << "Pawn";
	}
	if (pieceType == PieceType::Rook)
	{
		return out << "Rook";
	}
	if (pieceType == PieceType::Knight)
	{
		return out << "Knight";
	}
	if (pieceType == PieceType::Bishop)
	{
		return out << "Bishop";
	}
	if (pieceType == PieceType::Queen)
	{
		return out << "Queen";
	}
	if (pieceType == PieceType::King)
	{
		return out << "King";
	}
	else
	{
		return out << "Invalid piece";
	}
}

void chessIO::printBoard(const Chess& chess)
{
	const Player currentPlayer = chess.getCurrentPlayer();
	cout << currentPlayer << "'s turn";
	cout << endl;
	cout << "    A   B   C   D   E   F   G   H" << endl;
	cout << "   ";

	for (int col = 0; col < BOARD_SIZE * 4; col++)
	{
		cout << "_";
	}
	cout << endl;

	// Get the board
	Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

	for (int row = 0; row < BOARD_SIZE; row++)
	{
		cout << row + 1 << " ";
		cout << "| ";
		for (int col = 0; col < BOARD_SIZE; col++)
		{	
			PieceType pieceType = board[col][row]->getPieceType();
			Player player = board[col][row]->getPlayer();

			// Output which player the piece belongs to at the location
			if (player == Player::None)
			{
				cout << "+ ";
			}
			else if (player == Player::White)
			{
				cout << "W";
			}
			else if (player == Player::Black)
			{
				cout << "B";
			}

			// Output what type of piece is at the location
			if (pieceType == PieceType::Empty)
			{
				cout << " ";
			}
			else if (pieceType == PieceType::Pawn)
			{
				cout << "P ";
			}
			else if (pieceType == PieceType::Rook)
			{
				cout << "R ";
			}
			else if (pieceType == PieceType::Knight)
			{
				cout << "N ";
			}
			else if (pieceType == PieceType::Bishop)
			{
				cout << "B ";
			}
			else if (pieceType == PieceType::Queen)
			{
				cout << "Q ";
			}
			else if (pieceType == PieceType::King)
			{
				cout << "K ";
			}
			
			if (col < BOARD_SIZE - 1)
			{
				cout << " ";
			}
		}
		cout << "|";
		if (row < 7)
		{
			cout << endl << endl;
		}		
	}
	cout << endl << "   ";
	for (int col = 0; col < BOARD_SIZE * 4; col++)
	{
		cout << "-";
	}
	
	cout << endl << endl << endl << endl;
}

void chessIO::printMove(const Chess& chess, const Move& move)
{
	// Get the board
	Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();
	// Get the current player
	Player player = board[move.toCol][move.toRow]->getPlayer();

	cout << player << " Moved their " << board[move.toCol][move.toRow]->getPieceType() << " from "  << intToChar(move.fromCol) << move.fromRow << " to " << intToChar(move.toCol) << move.toRow << endl;
}

int chessIO::startMenu()
{
	int choice = 0;
	cout << "Welcome to Chess!" << endl;
	cout << "Enter 1 to start a new game." << endl;
	cout << "Enter 2 to load a previously saved game." << endl;
	cout << "Enter your choice here: ";
	cin >> choice;
	cout << endl;

	// Only accept 1 or 2
	while (choice < 1 || choice > 2)
	{
		cout << "Invalid input." << endl;
		cout << "Enter 1 to start a new game." << endl;
		cout << "Enter 2 to load a previously saved game." << endl;
		cout << "Enter your choice here: ";
		cin >> choice;
		cout << endl;
	}

	return choice;
}

void chessIO::printInvalidMove(std::ostream& out)
{
	out << "Invalid move" << endl;
}

const char chessIO::intToChar(const int& i)
{
	char c = static_cast<char>(i);
	return('A' + c);
}

const int chessIO::charToInt(const char& c)
{
	char upper = toupper(c);
	return upper - 'A';
}

Move chessIO::getMove()
{
	char from[3];
	char to[3];
	// Get the from and to locations from the user
	cout << "Enter the piece you would like to move: ";
	cin.getline(from, 3);
	cout << endl;
	cout << "Enter the destination location: ";
	cin.getline(to, 3);
	cout << endl;
	
	// Convert the input into type Move
	Move move;
	move.fromCol = charToInt(from[0]);
	move.fromRow = atoi(std::string(1, from[1]).c_str()) - 1;
	move.toCol = charToInt(to[0]);
	move.toRow = atoi(std::string(1, to[1]).c_str()) - 1;

	cout << move.fromCol  << " " << move.fromRow << " " << move.toCol << " " << move.toRow << " " << endl;

	// Validation checks
	bool isValid = false;
	while (!isValid)
	{
		if (inRange(move.fromCol, move.fromRow) && inRange(move.toCol, move.toRow))
		{
			isValid = true;
			return move;
		}
		else
		{
			// Print invalid input and call the function again
			cout << "Invalid input." << endl;
			cout << "Enter the piece you would like to move: ";
			cin.getline(from, 3);
			cout << endl;
			cout << "Enter the destination location: ";
			cin.getline(to, 3);
			cout << endl;

			move.fromCol = charToInt(from[0]);
			move.fromRow = atoi(std::string(1, from[1]).c_str()) - 1;
			move.toCol = charToInt(to[0]);
			move.toRow = atoi(std::string(1, to[1]).c_str()) - 1;
		}
	}
}

char chessIO::saveChoice()
{
	char choice;
	cout << "Would you like to create a new save (Y/N)? ";

	// Loop until valid input
	bool validChoice = false;
	while (!validChoice)
	{
		// Get the choice from the user
		cin >> choice;
		choice = toupper(choice);
		if (choice == 'Y' || choice == 'N')
		{
			validChoice = true;
		}
		else
		{
			validChoice = false;
			cout << endl;
			cout << "Invalid input. Enter Y to create a new save, or N to play without saving: ";
		}
	}
	
	cout << endl;
	return choice;
}


bool chessIO::inRange(int a, int b)
{
	if (a > BOARD_SIZE || a < 0 || b > BOARD_SIZE || b < 0)
	{
		cout << "Out of range" << endl;
		return false;		
	}
	else
	{
		return true;
	}
}

bool chessIO::fileExists(std::string file)
{
	return std::filesystem::exists(file);
}

bool chessIO::loadSavedGame(Chess& chess, std::string savedFile)
{
	// Open the file
	std::ifstream inputFile(savedFile);

	// Make sure the file is open
	if (!inputFile)
	{
		cout << "Error opening file '" << savedFile << "'." << endl;
		return false;
	}
	else
	{
		// Read the file and make the saved moves until there are no more moves
		int fromCol, fromRow, toCol, toRow;
		while (inputFile >> fromCol >> fromRow >> toCol >> toRow)
		{
			Move move = { fromCol, fromRow, toCol, toRow };
			chess.makeMove(move);
		}
		return true;
	}
}

void chessIO::saveGame(const vector<Move> moves, std::string& fileName)
{
	// Create the file
	std::ofstream file(fileName);

	// Make sure the file is open
	if (file.is_open())
	{
		for (int i = 0; i < moves.size(); i++)
		{
			file << moves.at(i).fromCol << " " << moves.at(i).fromRow << " " << moves.at(i).toCol << " " << moves.at(i).toRow << " ";
		}
		file << endl;

		// Close the file
		file.close();

		cout << "Game saved successfully." << endl;
	}
	else
	{
		cout << "Failed to save game. " << endl;
	}
}

std::string chessIO::createSaveName()
{
	std::string saveName;
	
	// Get the name of the file from the user
	cout << "Enter the name of the new save to create: ";
	cin >> saveName;
	cout << endl;

	saveName += ".txt";

	// Check if the file already exists
	if (!fileExists(saveName))
	{
		return saveName;
	}

	else
	{
		// Ask if the user wants to override the existing file
		char response;
		cout << " The name file name you entered is already in use. Would you like to override the existing file(Y/N)? ";
		cin >> response;
		response = toupper(response);

		if (response == 'Y')
		{
			return saveName;
		}
		else
		{
			createSaveName();
		}
	}
}

std::string chessIO::getExistingSaveName()
{
	std::string saveName;
	cout << "Enter the name of the save you would like to load. Enter 'Cancel' to return: ";
	// Maybe find a way to print the existing files
	cin >> saveName;
	if ((saveName) == "Cancel")
	{
		return saveName;
	}

	saveName += ".txt";
	
	// Check if the file already exists
	if (fileExists(saveName))
	{
		return saveName;
	}
	else
	{
		cout << "File does not exist." << endl;
		getExistingSaveName();
	}
}
