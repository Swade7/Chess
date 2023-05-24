#pragma once

#include "ChessLogic.hpp"
#include<iostream>
#include <ostream>
using std::cout;
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
};
