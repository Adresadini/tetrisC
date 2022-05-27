#include "Game.h"
#include "../Logging/Logger.h"

int main()
{
	Game x("PieceTypes.txt");
	x.ShowMenu();
	return 0;
}
