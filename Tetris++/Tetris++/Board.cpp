#include "Board.h"

const char EmptyBoardSpace = '_';
Board::Board(const uint16_t& width, const uint16_t& height, const bool& multiPlayer)
	:m_width(width), m_height(height), m_size(width* height)
{
	if (!multiPlayer && m_height < 3 * m_width || multiPlayer && m_height < 3 * m_width / 2)
		throw "Wrong board size";
	for (auto i = 0; i < m_size; i++)
		m_board.push_back(std::nullopt);
}

const std::optional<uint8_t>& Board::operator[](const Position& pos) const
{
	const auto& [line, column] = pos;
	if (line >= m_height || column >= m_width || line < 0 || column < 0)
		throw "Out of bounds";
	return m_board[line * m_width + column];
}

std::optional<uint8_t>& Board::operator[](const Position& pos)
{
	const auto& [line, column] = pos;
	if (line >= m_height || column >= m_width || line < 0 || column < 0)
		throw "Out of bounds";
	return m_board[line * m_width + column];
}

size_t Board::GetWidth() const
{
	return m_width;
}

size_t Board::GetHeight() const
{
	return m_height;
}



std::ostream& operator<<(std::ostream& out, const Board& board)
{
	Board::Position position;
	auto& [line, column] = position;
	for (line = 0; line < board.m_height; line++)
	{
		for (column = 0; column < board.m_width; column++)
		{
			if (board[position] && board[position] != 0) // TO DO VEZI DE CE NU MERGE resetPieceElement SI STERGE FAZA CU 0
				out << unsigned(*board[position]);
			else
				out << EmptyBoardSpace;
			out << " ";
		}

		out << std::endl;
	}
	return out;
}

void Board::DeleteCompleteLines()
{
	for (uint16_t line = 0; line < m_height; line++)
		if (VerifyIfLineIsComplete(line))
			DeleteAndReplaceLine(line);
}

bool  Board::VerifyIfLineIsComplete(const uint16_t& line) const
{
	for (uint16_t column = 0; column < m_width; column++)
		if (!m_board[line * m_width + column]) return false;
	return true;
}

void Board::DeleteAndReplaceLine(const uint16_t& line)
{
	m_board.erase(m_board.begin() + line * m_width, m_board.begin() + line * m_width + m_width);

	for (uint16_t index = 0; index < m_width; index++)
		m_board.insert(m_board.begin(), std::nullopt);
}