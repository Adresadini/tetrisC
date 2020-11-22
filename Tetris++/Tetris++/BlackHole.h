#pragma once
#include "Board.h"

class BlackHole
{
public:
	BlackHole() = default;
	void eat(Board& board);
	void disappear(Board& board);
private:
	uint8_t m_positionX;
	uint8_t m_positionY;
};


