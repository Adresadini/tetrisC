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

		board[{10, 3}] = 9;

		for (uint16_t column = 0; column < 7; column++)
			board[{9, column }] = 1;


		Player player("Player1", 420);
		std::cout << player.PlayerToString() << std::endl << board;
		tetrisPiece.RotateRight(board);

		BlackHole hole;
		hole.Spawn(board, tetrisPiece);

		board.DeleteCompleteLines();

		Sleep(1000);
		system("CLS");
		std::cout << player.PlayerToString() << std::endl << board;
		hole.Disappear(board);

		Sleep(1000);
		system("CLS");

		tetrisPiece.RotateRight(board);
		std::cout << player.PlayerToString() << std::endl << board;

		std::cout << scores;
	}
	catch (const char* errorMessage)
	{
		std::cout << errorMessage;
	}
	return 0;
}