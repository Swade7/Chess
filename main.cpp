#include "ChessLogic.hpp"
#include "ChessIO.hpp"

int main()
{
	Chess chess;
	chessIO io;
	io.printBoard(chess);
	return 0;
}