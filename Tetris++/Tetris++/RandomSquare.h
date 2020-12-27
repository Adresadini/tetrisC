#pragma once
#include"Board.h"
#include<optional>

class RandomSquare
{
private:
	Board::Position m_position;
	std::optional<uint8_t> m_value;
public:
	RandomSquare(Board& board);
	void MoveDown(Board& board);
	void Draw(Board& board);
	bool isSet(Board& board);
};

