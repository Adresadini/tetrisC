#pragma once
#include <iostream>
#include <queue>
#include <string>

#include "Player.h"

class Scores
{
public:
	
	Scores();
	
	friend std::istream& operator >>(std::istream&, std::priority_queue<Player>& );
	friend std::ostream& operator <<(std::ostream&, std::priority_queue<Player>& );

private:
	
	std::priority_queue <Player> m_queue;

};

