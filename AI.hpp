#pragma once

#include <iostream>
#include <fstream>
#include "Pieces.hpp"

struct MoveRanking
{
	Move move;
	int value;
};
class AI {
public:

	void train();
	static void randomMoves(Chess& chess);
	static Move calculatedRandom(Chess& chess);
private:
	
};

/*
Heres how I want it set up : I want to have each move start off with a default value,
and based upon the possible moves,
capturing certain pieces would add more weight
and putting certian pieces at risk of being captured lowers the weight.
I also want the weight to increase for all moves by the winning AI and decrease for the losing AI
*/