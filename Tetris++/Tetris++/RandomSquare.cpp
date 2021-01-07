#include "RandomSquare.h"
#include <random>

RandomSquare::RandomSquare(Board& board)
{
	m_position.first = 0;

	std::random_device random;
	std::uniform_int_distribution<uint16_t> columnDistribution(0, board.GetWidth() - 1);

	m_position.second = columnDistribution(random);
	while (board[m_position])
		m_position.second = columnDistribution(random);
	m_isSet = false;

	std::uniform_int_distribution<uint16_t> colorDistribution(1, 7);
	m_value = colorDistribution(random);

}

void RandomSquare::MoveDown(Board& board)
{
	m_lowestEmptyPosition = FindTheLowestEmptyPosition(board);
	if (m_position.first != m_lowestEmptyPosition)
	{
		Delete(board);
		m_previosBoardValue = board[{m_position.first + 1, m_position.second}];
		++m_position.first;
		Draw(board);
	}
	else
		m_isSet = true;
}

void RandomSquare::Draw(Board& board) const
{
	board[m_position] = m_value;
}

bool RandomSquare::isSet() const
{
	return m_isSet;
}

void RandomSquare::Delete(Board& board) const
{
	board[m_position] = m_previosBoardValue;
}

int16_t RandomSquare::FindTheLowestEmptyPosition(const Board& board)
{
	if (m_position.first == m_lowestEmptyPosition)
		return m_lowestEmptyPosition;
	for (int16_t line = board.GetHeight() - 1; line >= 0; line--)
		if (!board[{line, m_position.second}])
			return line;
	// TO DO :: vezi cum faci un throw aici sa se intample ceva daca gaseste o coloana full
}

Board::Position RandomSquare::getPosition() const
{
	return m_position;
}
