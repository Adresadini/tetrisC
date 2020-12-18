#include "Board.h"
#include "BlackHole.h"
#include "Player.h"
#include "TetrisPiece.h"
#include "Scores.h"
#include "PieceTypes.h"
#include "Game.h"
#include <fstream>
#include <windows.h>

int main1()
{
	try {
		Board::Position pos = { -2,1 };
		PieceTypes types("PieceTypes.txt");
		Scores scores;
		scores.ReadPlayers("Scores.txt");

		Board board(7, 21, 0);
		TetrisPiece tetrisPiece(pos, types);

		tetrisPiece.Draw(board);
		board[{2, 5}] = 9;

		//board[{10, 3}] = 9;

		for (uint16_t column = 0; column < 7; column++)
			board[{9, column }] = 1;
		for (uint16_t column = 0; column < 7; column++)
			board[{10, column }] = 1;

		Player player("Player1", 420);
		std::cout << player.PlayerToString() << std::endl << board;
		tetrisPiece.MoveRight(board);

		BlackHole hole;
		//hole.Spawn(board, tetrisPiece);

		board.DeleteCompleteLines();

		Sleep(3000);
		system("CLS");
		std::cout << player.PlayerToString() << std::endl << board;
		hole.Disappear(board);

		Sleep(3000);
		system("CLS");

		tetrisPiece.MoveRight(board);
		std::cout << player.PlayerToString() << std::endl << board;

		//std::cout << scores;
		scores.PrintPlayers("Scores.txt");
		/*std::ofstream out("Scores.txt");
		out << scores;*/
	}
	catch (const char* errorMessage)
	{
		std::cout << errorMessage;
	}
	return 0;
}

int main()
{
	Game x(9, 27, 0, "PieceTypes.txt");
	x.VisualInterface();
	return 0;
}
