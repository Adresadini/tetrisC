#include "Player.h"
#include <string>

Player::Player(std::string name, uint16_t score)
	:m_name(name), m_score(score)
{
	m_highScore = 0;
	m_averageScore = 0;
	m_scoreCount = 0;
}

std::string Player::PlayerToString() const
{
	return m_name + " " + std::to_string(m_score);
}

void Player::ModifyScoreInfo()
{
	m_averageScore = (m_averageScore * (m_scoreCount)+m_score) / (++m_scoreCount);
	if (m_score > m_highScore)
		m_highScore = m_score;
}

uint16_t Player::GetHighScore() const
{
	return m_highScore;
}

uint16_t Player::GetAverageScore() const
{
	return m_averageScore;
}

uint16_t Player::GetScore() const
{
	return m_score;
}

void Player::SetScore(uint16_t& score)
{
	m_score = score;
}

std::string Player::GetName() const
{
	return m_name;
}

void Player::SetName(std::string& name)
{
	m_name = name;
}

void Player::MoveLeft(TetrisPiece& piece)
{
	//piece.MoveLeft(board);
}

void Player::MoveRight(TetrisPiece& piece)
{
	//piece.MoveRight(board);
}
