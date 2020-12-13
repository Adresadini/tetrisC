#include "Player.h"
#include <string>

const std::string playerControls1 = { 'a','d','s','q','e' };
const std::string playerControls2 = { 'j','k','l','u','o' };

Player::Player(const std::string& name, const uint16_t& score, const bool isPlayerTwo)
	:m_name(name), m_score(score)
{
	m_highScore = 0;
	m_averageScore = 0;
	m_scoreCount = 0;
	!isPlayerTwo ? m_playerControls = playerControls1 : m_playerControls = playerControls2;
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

uint8_t Player::GetScoreCount() const
{
	return m_scoreCount;
}

void Player::SetScore(const uint16_t& score)
{
	m_score = score;
}

std::string Player::GetName() const
{
	return m_name;
}

void Player::SetName(const std::string& name)
{
	m_name = name;
}

void Player::MovePiece(TetrisPiece& piece, Board& board, bool gameOver)
{
	piece.MovePiece(board, gameOver);
}

std::ostream& operator<<(std::ostream& out, Player player)
{
	out << player.GetName() << " " << player.GetAverageScore() << " " << player.GetScoreCount();
	return out;
}
