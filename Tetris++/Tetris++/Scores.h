#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>

#include "Player.h"

class Scores
{
public:
	
	Scores()=default;
	
	void ReadPlayers(const std::string& fileName, Player);
	void PrintPlayers(const std::string &fileName);

	bool IsNewPlayer(const Player& player);

private:
	
	std::set<Player, std::greater<Player>> m_set;
};