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
	
	void ReadPlayers(const std::string& fileName);
	void PrintPlayers(const std::string &fileName);

	void GetPlayer(Player&);
	void UpdatePlayer(const Player&);

private:
	
	std::set<Player, std::greater<Player>> m_set;
};