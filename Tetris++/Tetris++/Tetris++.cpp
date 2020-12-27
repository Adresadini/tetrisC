#include "Game.h"
#include"RandomSquare.h"

int main()
{
	Board board(9, 27, 0);
	RandomSquare square(board);
}
int main2()
{
	Game x(9, 27, 0, "PieceTypes.txt");
	x.VisualInterface();
	//x.Run();
	return 0;
}
