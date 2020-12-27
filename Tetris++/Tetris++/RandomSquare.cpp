#include "RandomSquare.h"
#include <random>

RandomSquare::RandomSquare(Board& board)
{
	m_position.first = -1;

	std::random_device random;
	std::uniform_int_distribution<uint16_t> columnDistribution(0, board.GetWidth() - 1);

	m_position.second = columnDistribution(random);
}

void RandomSquare::MoveDown(Board& board)
{
	if (m_position.first != board.GetHeight() - 1 &&
		board[{m_position.first - 1, m_position.second}] == std::nullopt)
		++m_position.first;

}

void RandomSquare::Draw(Board& board)
{
	if (board[m_position] == 0)
		m_value = std::nullopt;
	board[m_position] = m_value;
}
