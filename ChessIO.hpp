#pragma once

#include "Pieces.hpp"
#include<iostream>
#include <ostream>
#include<fstream>
using std::cout;
using std::cin;
using std::endl;


class chessIO
{
public:

	// Operators
	friend std::ostream& operator << (std::ostream& out, Player const& player);
	friend std::ostream& operator << (std::ostream& out, PieceType const& pieceType);

	static void printBoard(const Chess& chess);
	void printMove(const Chess& chess, const Move& move);
	void printInvalidMove(std::ostream& out);
	const char intToChar(const int& i);
	const int charToInt(const char& c);
	bool inRange(int a, int b);
	void saveGame(const Chess& chess, std::string& file);

	// Getters
	Move getMove();
};
