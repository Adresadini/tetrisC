#pragma once
#include <array>
#include <iostream>
#include <optional>
#include "Board.h"
class TetrisPiece
{
public:
	TetrisPiece();
	enum class Body :uint8_t
	{
		Cyan,
		Blue,
		Orange,
		Yellow,
		Green,
		Purple,
		Red,
		None
	};
	void MoveLeft();
	void MoveDown(const Board);
	void MoveRight(const Board);
private:
	uint8_t m_positionX;
	uint8_t m_positionY;
	using m_pieceType = std::array<std::array<uint8_t, 4>, 6>;
	Body m_color : 7;
	static const size_t kWidth = 4;
	static const size_t kHeight = 4;
	static const size_t kSize = kWidth * kHeight;
	std::array<std::optional<uint8_t>, kSize> m_piece;
};

