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
	
	void ReadPlayers(std::string fileName);
	void PrintPlayers(std::string &fileName);
	
	friend std::ostream& operator <<(std::ostream&, Scores& );
	
	bool IsNewPlayer(Player& player);

private:
	
	std::map<std::string, uint16_t> m_map;
};