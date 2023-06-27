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
