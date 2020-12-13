#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

#include "Player.h"

class Scores
{
public:
	
	Scores()=default;
	
	void ReadPlayers(const std::string& fileName);
	void PrintPlayers(const std::string &fileName);
	
	friend std::ostream& operator <<(std::ostream&, Scores& );

	bool IsNewPlayer(const Player& player);

private:
	
	std::map<Player, uint16_t> m_map;
};