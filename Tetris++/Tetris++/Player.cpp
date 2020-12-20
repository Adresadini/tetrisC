#include "Player.h"
#include <string>

Player::Player(const std::string& name, const uint16_t& score, const bool isPlayerTwo)
	:m_name(name), m_score(score)
{
	m_highScore = 0;
	m_averageScore = 0;
	m_scoreCount = 0;
	InitKeyBindings(isPlayerTwo);
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

void Player::SetHighScore(uint16_t highScore)
{
	m_highScore = highScore;
}

uint16_t Player::GetAverageScore() const
{
	return m_averageScore;
}

void Player::SetAverageScore(uint16_t averageScore)
{
	m_averageScore = averageScore;
}

uint16_t Player::GetScore() const
{
	return m_score;
}

uint8_t Player::GetScoreCount() const
{
	return m_scoreCount;
}

void Player::SetScoreCount(uint16_t scoreCount)
{
	m_scoreCount = scoreCount;
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

void Player::InitKeyBindings(bool isPlayerTwo)
{
	//Initializing player keybinds in the following order: left, right, down, rotate left, rotate right
	if (!isPlayerTwo) //For Player 1
	{
		m_input.push_back(sf::Keyboard::A);
		m_input.push_back(sf::Keyboard::D);
		m_input.push_back(sf::Keyboard::S);
		m_input.push_back(sf::Keyboard::Q);
		m_input.push_back(sf::Keyboard::E);
	}
	else //For Player 2
	{
		m_input.push_back(sf::Keyboard::Numpad4);
		m_input.push_back(sf::Keyboard::Numpad6);
		m_input.push_back(sf::Keyboard::Numpad5);
		m_input.push_back(sf::Keyboard::Numpad7);
		m_input.push_back(sf::Keyboard::Numpad9);
	}
}

void Player::MovePiece(TetrisPiece& piece, Board& board, bool gameOver)
{
	piece.MovePiece(board, gameOver);
}

bool Player::operator>(const Player& player) const
{
	return player.GetHighScore() > this->GetHighScore();
}

std::ostream& operator<<(std::ostream& out, Player player)
{
	out << player.GetName() << " " << player.GetAverageScore() << " " << player.GetScoreCount() << " " << player.GetHighScore();
	return out;
}

std::istream& operator>>(std::istream& in, Player player)
{
	in >> player.m_name >> player.m_averageScore >> player.m_scoreCount >> player.m_highScore;
	return in;
}


