#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <vector>

#include "Player.h"

class Scores
{
public:
	
	Scores()=default;
	
	friend std::istream& operator >>(std::istream&, std::priority_queue<Player>& );
	void ReadPlayers(std::string fileName);
	friend std::ostream& operator <<(std::ostream&, Scores& );
	bool IsNewPlayer(Player& player);

private:
	
	std::vector<Player> m_vector;
	//std::priority_queue <Player> m_queue;
};