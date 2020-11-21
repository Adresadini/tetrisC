#include "Player.h"

Player::Player(std::string name = NULL, uint16_t score = 0)
	:m_name(name), m_score(score)
{

}

std::istream& operator>>(std::istream& in, Player& player)
{
	in >> player.m_name >> player.m_score;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
	out << player.m_name << " " << player.m_score << std::endl;
	return out;
}
