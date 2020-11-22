#include "TetrisPiece.h"
void TetrisPiece::MoveLeft()
{
	if (m_positionX > 0)
		m_positionX--;
}

void TetrisPiece::MoveDown(const Board board)
{
	if (m_positionY < board.getHeight())
	m_positionY--;
}

void TetrisPiece::MoveRight(const Board board)
{
	if (m_positionX < board.getWidth())
		m_positionX++;
}
