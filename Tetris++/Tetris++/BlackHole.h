#pragma once
#include "Board.h"

class BlackHole
{
public:
	BlackHole() = default;
	void eat(Board& board);
	void disappear(Board& board);
private:
	int m_positionX;
	int m_positionY;
};


