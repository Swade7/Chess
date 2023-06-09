#include "AI.hpp"
#include <random>

const int pawnVal = 3;
const int knightVal = 6;
const int bishopVal = 8;
const int rookVal = 12;
const int queenVal = 25;
const int checkVal = 10;
const int checkmateVal = 40;

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
	

	// Define the default value for a move
	const int defaultRanking = 1;

	// Get the possible moves
	const vector<Move> possibleMoves = chess.GetPossibleMoves();

	// Get the board
	Pieces* const (&board)[BOARD_SIZE][BOARD_SIZE] = chess.getBoard();

	// Create a copy of the board to test possible moves
	//Chess chessCopy = chess;

	// Get the current player
	Player currentPlayer = chess.getCurrentPlayer();
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
			moveRankings.at(i).value += getPieceValue(board[currentMove.toCol][currentMove.toRow]->getPieceType());
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
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			for (int row = 0; row < BOARD_SIZE; row++)
			{
				if (board[col][row]->getPlayer() == currentPlayer)
				{
					if (chess.underAttack(col, row))
					{
						// Make a copy of the board and check if the piece would still be under attack after making the move
						// Where I left off

						for (int i = 0; i < possibleMoves.size(); i++)
						{
							Chess chessCopy = chess;
							chessCopy.makeMove(moveRankings.at(i).move);

							// Check if the piece is still under attack after the move
							if (!chessCopy.underAttack(col, row))
							{
								moveRankings.at(i).value += getPieceValue(board[col][row]->getPieceType());
							}
							else
							{	
								int pieceValue = getPieceValue(board[col][row]->getPieceType());
								if ((moveRankings.at(i).value - pieceValue) >= 0)
								{
									moveRankings.at(i).value -= pieceValue;
								}
							}
						}
						
					}
				}
			}
		}
		
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
	std::uniform_int_distribution<int> dist(0, moveRankings.size() - 1);
	int randomNumber = dist(rng);

	Move bestMove = possibleMoves.at(randomNumber);

	for (int i = 0; i < moveRankings.size(); i++)
	{
		if (moveRankings.at(i).value > moveRankings.at(randomNumber).value)
		{
			bestMove = possibleMoves.at(i);
		}
	}

	// return the move
	//return weightedMoves.at(randomNumber);
	return bestMove;
}

int AI::getPieceValue(PieceType pieceType)
{
	if (pieceType == PieceType::Pawn)
	{
		return pawnVal;
	}
	else if (pieceType == PieceType::Knight)
	{
		return knightVal;
	}
	else if (pieceType == PieceType::Bishop)
	{
		return bishopVal;
	}
	else if (pieceType == PieceType::Rook)
	{
		return rookVal;
	}
	else if (pieceType == PieceType::Queen)
	{
		return queenVal;
	}
	else
	{
		return 0;
	}
}
