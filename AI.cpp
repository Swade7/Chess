#include "AI.hpp"
#include <random>

void AI::randomMoves(Chess& chess)
{
	const vector<Move> possibleMoves = chess.GetPossibleMoves();
	
	// Get a random number
	std::random_device random;
	std::mt19937 rng(random());
	std::uniform_int_distribution<int> dist(0, possibleMoves.size() - 1);
	int randomNumber = dist(rng);

	// Make the move
	chess.makeMove(possibleMoves.at(randomNumber));
}

Move AI::calculatedRandom(Chess& chess)
{
	// Define values for each piece and possible scenarios
	const int pawnVal = 3;
	const int knightVal = 6;
	const int bishopVal = 8;
	const int rookVal = 12;
	const int queenVal = 25;
	const int checkVal = 10;
	const int checkmateVal = 40;

	// Define the default value for a move
	const int defaultRanking = 1;

	// Get the possible moves
	const vector<Move> possibleMoves = chess.GetPossibleMoves();

	// Get the board
	Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

	// Create a copy of the board to test possible moves
	//Chess chessCopy = chess;

	// Get the opponent
	Player opponent = chess.getOpponent();

	// Put the possible moves in a vector of type MoveRanking
	vector<MoveRanking> moveRankings;
	for (int i = 0; i < possibleMoves.size(); i++)
	{
		MoveRanking move = { possibleMoves.at(i), defaultRanking };
		moveRankings.push_back(move);
	}

	// Iterate through the possible moves and update the value of the move based on the potential outcome
	for (int i = 0; i < moveRankings.size(); i++)
	{
		Move currentMove = moveRankings.at(i).move;

		// If capturing a piece, increase the move value an amount dependent on what is being captured
		if (board[currentMove.toCol][currentMove.toRow]->getPlayer() == opponent)
		{
			if (board[currentMove.toCol][currentMove.toRow]->getPieceType() == PieceType::Pawn)
			{
				moveRankings.at(i).value += pawnVal;
			}
			else if (board[currentMove.toCol][currentMove.toRow]->getPieceType() == PieceType::Knight)
			{
				moveRankings.at(i).value += knightVal;
			}
			else if (board[currentMove.toCol][currentMove.toRow]->getPieceType() == PieceType::Bishop)
			{
				moveRankings.at(i).value += bishopVal;
			}
			else if (board[currentMove.toCol][currentMove.toRow]->getPieceType() == PieceType::Rook)
			{
				moveRankings.at(i).value += rookVal;
			}
			else if (board[currentMove.toCol][currentMove.toRow]->getPieceType() == PieceType::Queen)
			{
				moveRankings.at(i).value += queenVal;
			}
		}

		// Check if the move would put the opponent in check
		for (int i = 0; i < moveRankings.size(); i++)
		{
			// Create a copy of the chess game to test
			Chess chessCopy = chess;

			chessCopy.makeMove(moveRankings.at(i).move);
			if (chessCopy.check())
			{
				// Check if it would put the opponent in checkmate
				if (chessCopy.checkmate())
				{
					moveRankings.at(i).value += checkmateVal;
				}
				else
				{
					moveRankings.at(i).value += checkVal;
				}
			}
		}	

		// Check if any pieces are currently under attack and if the move would protect the piece

		
		// Check if the move would put pices under attack

	}

	// Add each possible move to a vector x the value
	vector <Move> weightedMoves;
	for (int i = 0; i < moveRankings.size(); i++)
	{
		for (int j = 0; j < moveRankings.at(i).value; j++)
		{
			weightedMoves.push_back(possibleMoves.at(i));
		}
	}

	// Get a random move with better moves having higher odds
	std::random_device random;
	std::mt19937 rng(random());
	std::uniform_int_distribution<int> dist(0, weightedMoves.size() - 1);
	int randomNumber = dist(rng);

	// Make the move
	//chess.makeMove(weightedMoves.at(randomNumber));
	return weightedMoves.at(randomNumber);
}
