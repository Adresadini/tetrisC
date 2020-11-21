#include "Board.h"
#include "BlackHole.h"
#include <windows.h> // l-am pus pt sleep , il stergem dupa


int main()
{
	try {
		Board board(7, 21, 0);
		board[{1,3}] = 3;
		std::cout << board;
		BlackHole hole;
		hole.eat(board);
		Sleep(3000);
		system("CLS");
		std::cout << board;
		hole.disappear(board);
		Sleep(3000);
		system("CLS");
		std::cout << board;
	}
	catch (const char* errorMessage)
	{
		std::cout << errorMessage;
	}
}