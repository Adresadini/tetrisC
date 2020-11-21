#include "BlackHole.h"
#include <time.h>

void BlackHole::eat(Board& board)
{
	srand(time(NULL));
	m_positionX = rand() % board.getHeight();
	m_positionY = rand() % board.getWidth();
	if (board[{m_positionX, m_positionY}] == std::nullopt)
		board[{m_positionX, m_positionY}] = 0;
	else board[{m_positionX, m_positionY}] = std::nullopt;
}

void BlackHole::disappear(Board& board)
{
	board[{m_positionX, m_positionY}] = std::nullopt;
}




