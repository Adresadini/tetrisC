#include "Player.h"
#include <string>

Player::Player(const std::string& name, const bool isPlayerTwo)
	:m_name(name)
{
	InitKeyBindings(isPlayerTwo);
}

std::string Player::PlayerToString() const
{
	return m_name + " " + std::to_string(m_score);
}

void Player::ModifyScoreInfo()
{
	m_scoreCount++;
	m_averageScore = (m_averageScore * (m_scoreCount - 1) + m_score) / (m_scoreCount);
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

uint16_t Player::GetScoreCount() const
{
	return m_scoreCount;
}

void Player::AddScore(const uint16_t& score)
{
	m_score += score;
}

std::string Player::GetName() const
{
	return m_name;
}

void Player::SetInfo(const uint16_t& highScore, const uint16_t& averageScore, const uint16_t& scoreCount)
{
	m_highScore = highScore;
	m_averageScore = averageScore;
	m_scoreCount = scoreCount;
}

void Player::InitKeyBindings(bool isPlayerTwo)
{
	//Initializing player keybinds in the following order: Left, Right, Down, Rotate Right, Rotate Left, Scale, Drop Down
	if (!isPlayerTwo)
		m_input = { sf::Keyboard::Key::A, sf::Keyboard::Key::D, sf::Keyboard::Key::S, sf::Keyboard::Key::Q, sf::Keyboard::Key::E, sf::Keyboard::Key::W ,sf::Keyboard::Key::Space };
	else
		m_input = { sf::Keyboard::Key::Numpad4, sf::Keyboard::Key::Numpad6, sf::Keyboard::Key::Numpad2, sf::Keyboard::Key::Numpad7, sf::Keyboard::Key::Numpad9,sf::Keyboard::Key::Numpad8,sf::Keyboard::Key::Numpad5 };
}

void Player::MovePiece(const sf::Event& event, TetrisPiece& piece, Board& board)
{
	if (event.key.code == m_input[0])
	{
		piece.MoveLeft(board);
		return;
	}
	if (event.key.code == m_input[1])
	{
		piece.MoveRight(board);
		return;
	}
	if (event.key.code == m_input[2])
	{
		piece.MoveDown(board);
		return;
	}
	if (event.key.code == m_input[3])
	{
		piece.RotateLeft(board);
		return;
	}
	if (event.key.code == m_input[4])
	{
		piece.RotateRight(board);
		return;
	}
	if (event.key.code == m_input[5])
	{
		piece.Scale(board);
		return;
	}
	if (event.key.code == m_input[6])
	{
		piece.DropDown(board);
		return;
	}
}

bool Player::operator==(Player player)
{
	return (this->GetName() == player.GetName());
}

bool Player::operator<(const Player& player) const
{
	return player.GetHighScore() < this->GetHighScore();
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
	out << player.GetName() << " " << player.GetAverageScore() << " " << player.GetScoreCount() << " " << player.GetHighScore();
	return out;
}

std::istream& operator>>(std::istream& in, Player& player)
{
	in >> player.m_name >> player.m_averageScore >> player.m_scoreCount >> player.m_highScore;
	return in;
}


