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
	static void printMove(const Chess& chess, const Move& move);
	static int startMenu();
	static void printInvalidMove(std::ostream& out);


	static const char intToChar(const int& i);
	static const int charToInt(const char& c);
	static bool inRange(int a, int b);

	// Getters
	static Move getMove();

	// Setters
	static void saveGame(const Chess& chess, std::string& file);
};
