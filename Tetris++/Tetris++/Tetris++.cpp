#include "Board.h"



int main()
{
	try {
		Board board(10, 30, 0);
		std::cout << board;
		board[{14,3}] = 3;
		std::cout << board;
	}
	catch (const char* errorMessage)
	{
		std::cout << errorMessage;
	}
}