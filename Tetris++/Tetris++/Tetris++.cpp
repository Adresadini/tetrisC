#include "Board.h"
#include "BlackHole.h"
#include "Player.h"
#include "TetrisPiece.h"
#include <windows.h> // l-am pus pt sleep , il stergem dupa


int main()
{
	try {
		Board board(7, 21, 0);
		TetrisPiece tetrisPiece(4,2,6);
		tetrisPiece.Draw(board);
		board[{1, 3}] = 3;
		Player player("Player1", 420);
		std::cout << player << board;
		tetrisPiece.Delete(board);
		tetrisPiece.MoveDown(board);
		tetrisPiece.Draw(board);
		BlackHole hole;
		hole.eat(board);
		Sleep(3000);
		system("CLS");
		std::cout << player << board;
		hole.disappear(board);
		Sleep(3000);
		system("CLS");
		std::cout << player << board;
	}
	catch (const char* errorMessage)
	{
		std::cout << errorMessage;
	}
}