#pragma once
#include"Board.h"
#include<optional>

class RandomSquare
{
private:
	Board::Position m_position;
	std::optional<uint8_t> m_value;
	bool m_isSet;
	int16_t m_lowestEmptyPosition;
	std::optional<uint8_t> m_previosBoardValue;
public:
	RandomSquare(Board& board);
	void MoveDown(Board& board);
	void Draw(Board& board) const;
	bool isSet() const;
	void Delete(Board& board) const;
	void DeleteColmpletLine(Board& board) const;
	int16_t FindTheLowestEmptyPosition(const Board& board);
	Board::Position getPosition() const;
};

