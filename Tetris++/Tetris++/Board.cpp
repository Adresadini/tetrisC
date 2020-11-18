#include "Board.h"

const char EmptyBoardSpace = '_';
Board::Board(uint16_t width, uint16_t height, bool multiPlayer)
	:m_width(width), m_height(height), m_size(width* height)
{
	if (!multiPlayer && m_height < 3 * m_width || multiPlayer && m_height < 3 * m_width / 2)
		throw "Wrong board size";
	std::vector<std::optional<uint8_t>>board(m_size,std::nullopt);
	this->m_board = board;
}

const std::optional<uint8_t>& Board::operator[](const Position& pos) const
{
	const auto& [line, column] = pos;
	if (line >= m_height || column >= m_width)
		throw "Out of bounds";
	return m_board[line * m_width + column];
}

std::optional<uint8_t>& Board::operator[](const Position& pos)
{
	const auto& [line, column] = pos;
	if (line >= m_height || column >= m_width)
		throw "Out of bounds";
	return m_board[line * m_width + column];
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
	Board::Position position;
	auto& [line, column] = position;
	for (line = 0; line < board.m_height; line++)
	{
		for (column = 0; column < board.m_width; column++)
		{
			if (board[position])
				out << *board[position];
			else
				out << EmptyBoardSpace;
			out << " ";
		}

		out << std::endl;
	}
	return out;
}
