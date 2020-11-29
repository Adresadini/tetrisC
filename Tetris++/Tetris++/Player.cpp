#include "Player.h"
#include <string>

uint16_t Player::m_highScore;
uint16_t Player::m_averageScore;
uint8_t Player::m_scoreCount;

Player::Player(std::string name, uint16_t score)
	:m_name(name), m_score(score)
{

}

std::string Player::PlayerToString()
{
	return m_name + " " + std::to_string(m_score);
}

void Player::ModifyScoreInfo()
{
	m_averageScore = (m_averageScore * (m_scoreCount)+m_score) / (++m_scoreCount);
	if (m_score > m_highScore)
		m_highScore = m_score;
}

uint16_t Player::GetHighScore()
{
	return m_highScore;
}

uint16_t Player::GetAverageScore()
{
	return m_averageScore;
}

uint16_t Player::GetScore()
{
	return m_score;
}

std::string Player::GetName()
{
	return m_name;
}