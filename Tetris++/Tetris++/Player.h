#pragma once
#include <iostream>

class Player
{
public:
	Player(std::string name, uint16_t score);
	friend std::istream& operator>>(std::istream&, Player&);
	friend std::ostream& operator<<(std::ostream&, const Player&);

private:
	std::string m_name;
	uint16_t m_score;
};

