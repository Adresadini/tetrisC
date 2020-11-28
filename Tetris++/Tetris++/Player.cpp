#include "Player.h"
#include <string>

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
	m_average = (m_average * (m_scoreCount)+m_score) / (++m_scoreCount);
	if (m_score > m_highScore)
		m_highScore = m_score;
}
