#include "Game.h"

/*Use #include "../Logging/Logger.h"
in order to use the Logger
*/

int main()
{
	Game x(9, 27, 0, "PieceTypes.txt");
	x.VisualInterface();
	return 0;
}
