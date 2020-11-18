#include "Board.h"

Board::Board(uint16_t width, uint16_t height, bool multiPlayer)
	:m_width(width), m_height(height), m_size(width* height)
{
	if (!multiPlayer && m_height < 3 * m_width || multiPlayer && m_height < 3 * m_width / 2)
		throw "Wrong board size";
}
