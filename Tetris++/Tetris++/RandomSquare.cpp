#include "RandomSquare.h"
#include <random>

RandomSquare::RandomSquare(Board& board)
{
	m_position.first = 0;

	std::random_device random;
	std::uniform_int_distribution<uint16_t> columnDistribution(0, board.GetWidth() - 1);

	m_position.second = columnDistribution(random);

	m_isSet = false;

	std::uniform_int_distribution<uint16_t> colorDistribution(1,7);
	m_value = colorDistribution(random);
}

void RandomSquare::MoveDown(Board& board)
{
	if (m_position.first != board.GetHeight() - 1 &&
		!board[{m_position.first + 1, m_position.second}]|| board[{m_position.first + 1, m_position.second}]==0)
	{
		Delete(board);
		++m_position.first;
		Draw(board);
	}
	else
	 m_isSet = true;

}

void RandomSquare::Draw(Board& board)
{
	if (board[m_position] == 0)
	{
		m_value = std::nullopt;
		m_isSet = true;
	}
	else
		board[m_position] = m_value;
}

bool RandomSquare::isSet()
{
	return m_isSet;
}

void RandomSquare::Delete(Board& board)
{
	board[m_position] = std::nullopt;
}
