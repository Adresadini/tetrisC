#include "TetrisPiece.h"
TetrisPiece::TetrisPiece(uint8_t positionX, uint8_t positionY)
	:m_positionX(positionX), m_positionY(positionY)
{
	m_piece[2] = 1;
	m_piece[6] = 1;
	m_piece[10] = 1;
	m_piece[14] = 1;
}
void TetrisPiece::MoveLeft()
{
	if (m_positionY > 0)
		m_positionY--;
}

void TetrisPiece::MoveDown(const Board board)
{
	if (m_positionX < board.getHeight())
	m_positionX++;
}

void TetrisPiece::MoveRight(const Board board)
{
	if (m_positionY < board.getWidth())
		m_positionY++;
}

void TetrisPiece::Draw(Board &board)
{
	uint8_t iterator = 0;
	for (uint8_t line = m_positionX; line < m_positionX + kHeight; line++)
		for (uint8_t column = m_positionY; column < m_positionY + kWidth; column++)
		{
			board[{line, column}] = m_piece[iterator];
			iterator++;
		}
}

void TetrisPiece::Delete(Board& board)
{
	for (uint8_t line = m_positionX; line < m_positionX + kHeight; line++)
		for (uint8_t column = m_positionY; column < m_positionY + kWidth; column++)
		{
			board[{line, column}] = std::nullopt;
		}
}
