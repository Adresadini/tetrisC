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

void Player::InitKeyBindings(bool isPlayerTwo)
{
	//Initializing player keybinds in the following order: left, right, down, rotate left, rotate right
	if (!isPlayerTwo)
		m_input = new sf::Keyboard::Key[5]{ sf::Keyboard::Key::A, sf::Keyboard::Key::D, sf::Keyboard::Key::S, sf::Keyboard::Key::Q, sf::Keyboard::Key::E };
	else
		m_input = new sf::Keyboard::Key[5]{ sf::Keyboard::Key::Numpad4, sf::Keyboard::Key::Numpad6, sf::Keyboard::Key::Numpad5, sf::Keyboard::Key::Numpad7, sf::Keyboard::Key::Numpad9 };
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


