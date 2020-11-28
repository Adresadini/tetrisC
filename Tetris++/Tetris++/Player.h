#pragma once
#include <iostream>

class Player
{
public:
	Player(std::string name = NULL, uint16_t score = 0);
	std::string PlayerToString();

private:
	std::string m_name;
	uint16_t m_score;
};

