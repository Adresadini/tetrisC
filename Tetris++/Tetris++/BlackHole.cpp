#include "BlackHole.h"

#include <random>

void BlackHole::Spawn(Board& board, TetrisPiece& tetrisPiece)
{
	std::random_device randomNumber;
	std::uniform_int_distribution<uint16_t> lineDistribution(0, board.GetHeight() - 1);
	std::uniform_int_distribution<uint16_t> columnDistribution(0, board.GetWidth() - 1);

	m_spawnPosition.first = lineDistribution(randomNumber);
	m_spawnPosition.second = columnDistribution(randomNumber);

	if (FoundAPiece(board, tetrisPiece))
	{
		tetrisPiece.ResetPieceElement(m_spawnPosition);
		board[m_spawnPosition] = std::nullopt;
	}
	else if (!board[m_spawnPosition])
		board[m_spawnPosition] = 0;
	else board[m_spawnPosition] = std::nullopt;
}

void BlackHole::Disappear(Board& board) const
{
	board[m_spawnPosition] = std::nullopt;
}



bool BlackHole::FoundAPiece(const  Board& board, TetrisPiece& piece) const
{
	return m_spawnPosition.first >= piece.GetPosition().first &&

		m_spawnPosition.first < piece.GetPosition().first + piece.GetKHeight() &&

		m_spawnPosition.second >= piece.GetPosition().second &&

		m_spawnPosition.second < piece.GetPosition().second + piece.GetKWidth() &&

		board[m_spawnPosition];
}
