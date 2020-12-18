#include "BlackHole.h"
#include <random>

void BlackHole::Spawn(Board& board, TetrisPiece& tetrisPiece)
{
	std::random_device randomNumber;
	std::uniform_int_distribution<uint16_t> lineDistribution(5, board.GetHeight() - 1);
	std::uniform_int_distribution<uint16_t> columnDistribution(0, board.GetWidth() - 1);

	m_spawnPosition.first = lineDistribution(randomNumber);
	m_spawnPosition.second = columnDistribution(randomNumber);

	if (!board[m_spawnPosition])
		board[m_spawnPosition] = 0;
	else board[m_spawnPosition] = std::nullopt;
}

void BlackHole::Disappear(Board& board) const
{
	board[m_spawnPosition] = std::nullopt;
}
