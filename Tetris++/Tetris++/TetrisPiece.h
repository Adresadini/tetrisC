#pragma once
#include <array>
#include <iostream>
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
private:
	int m_positionX;
	int m_positionY;
	using m_piece = std::array<std::array<uint8_t, 4>, 6>;
	Body m_color : 7;
};

