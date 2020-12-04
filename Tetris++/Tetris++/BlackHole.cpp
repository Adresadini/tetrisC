#include "BlackHole.h"
#include <random>

void BlackHole::Spawn(Board& board, TetrisPiece& tetrisPiece)
{
	std::random_device randomNumber;
	std::uniform_int_distribution<uint16_t> lineDistribution(0, board.getHeight() - 1);
	std::uniform_int_distribution<uint16_t> columnDistribution(0, board.getWidth() - 1);

	m_spawnPosition.first = lineDistribution(randomNumber);
	m_spawnPosition.second = columnDistribution(randomNumber);

	if (FoundAPiece(board, tetrisPiece))
		EatPiece(board, tetrisPiece);
	else if (!board[m_spawnPosition])
		board[m_spawnPosition] = 0;
	else board[m_spawnPosition] = std::nullopt;
}

void BlackHole::Disappear(Board& board) const
{
	board[m_spawnPosition] = std::nullopt;
}

void BlackHole::EatPiece(Board& board, TetrisPiece& piece) const
{
	for (size_t line = piece.GetPosition().first - 1; line <= m_spawnPosition.first; line++)
		for (size_t column = piece.GetPosition().second - 1; column <= m_spawnPosition.second; column++)
			piece.resetPieceElement(line * piece.GetKWidth() + column);
}

bool BlackHole::FoundAPiece(const  Board& board, TetrisPiece& piece) const
{
	return m_spawnPosition.first >= piece.GetPosition().first &&

		m_spawnPosition.first < piece.GetPosition().first + piece.GetKHeight() &&

		m_spawnPosition.second >= piece.GetPosition().second &&

		m_spawnPosition.second < piece.GetPosition().second + piece.GetKWidth() &&

		board[m_spawnPosition];
}