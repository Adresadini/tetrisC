#include "BlackHole.h"
#include <random>

void BlackHole::Spawn(Board& board)
{
	std::random_device randomNumber;
	std::uniform_int_distribution<size_t> lineDistribution(0, board.getHeight()-1);
	std::uniform_int_distribution<size_t> columnDistribution(0, board.getWidth()-1);
	m_spawnPosition.first = lineDistribution(randomNumber);
	m_spawnPosition.second = columnDistribution(randomNumber);
	if (board[m_spawnPosition] == std::nullopt)
		board[m_spawnPosition] = 0;
	else board[m_spawnPosition] = std::nullopt;
}

void BlackHole::Disappear(Board& board) const
{
	board[m_spawnPosition] = std::nullopt;
}




