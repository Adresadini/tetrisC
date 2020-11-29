#include "Board.h"
#include "BlackHole.h"
#include "Player.h"
#include "TetrisPiece.h"
#include "Scores.h"
#include <windows.h>

int main()
{
	try {

		Scores scores;
		scores.ReadPlayers("Scores.txt");
		
		Board board(7, 21, 0);
		TetrisPiece tetrisPiece({ 3,2 }, 6);
		tetrisPiece.Draw(board);

		//board[{6, 3}] = 3;

		Player player("Player1", 420);
		std::cout << player.PlayerToString() << board;
		tetrisPiece.RotateRight(board);

		BlackHole hole;
		hole.Spawn(board, tetrisPiece);

		Sleep(3000);
		system("CLS");
		std::cout << player.PlayerToString() << board;
		hole.Disappear(board);

		Sleep(3000);
		system("CLS");

		tetrisPiece.RotateRight(board);
		std::cout << player.PlayerToString() << board;
		
		std::cout << scores;
	}
	catch (const char* errorMessage)
	{
		std::cout << errorMessage;
	}
	return 0;
}