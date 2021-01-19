#include "Board.h"


const char EmptyBoardSpace = '_';
Board::Board(const uint16_t& width, const uint16_t& height, const bool& multiPlayer)
	:m_width(width), m_height(height)
{
	if (!multiPlayer && m_height < 3 * m_width || multiPlayer && m_height < 3 * m_width / 2)
		throw "Wrong board size";
	if (multiPlayer)
	{
		m_width *= 2;

	}

	m_size = m_width * m_height;

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
			if (board[position])
				out << unsigned(*board[position]);
			else
				out << EmptyBoardSpace;
			out << " ";
		}

		out << std::endl;
	}
	return out;
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

void Board::DeleteAndReplaceElement(const uint16_t& line, const uint16_t& column)
{
	for (uint16_t index = line; index > 0; index--)
		m_board[index * m_width + column] = m_board[(index - 1) * m_width + column];
	m_board[column] = std::nullopt;
}

void Board::VerifyIfAnyPlayerHaveALineComplete(const uint16_t& line, const bool& isPlayerTwo)
{
	uint8_t downLimit = isPlayerTwo * 20;
	uint8_t upLimit = isPlayerTwo * 20 + 20;

	uint8_t numberOfSameElements = 0;

	for (uint16_t column = 0; column < m_width; column++)
	{
		if (m_board[line * m_width + column] != std::nullopt &&
			m_board[line * m_width + column] > downLimit &&
			m_board[line * m_width + column] < upLimit)
			numberOfSameElements++;
		else
		{
			if (numberOfSameElements >= m_width / 2)
			{
				DeletePlayerLine(line, column, numberOfSameElements);
				return;
			}
			numberOfSameElements = 0;
		}
		if (numberOfSameElements >= m_width / 2)
		{
			DeletePlayerLine(line , column, numberOfSameElements);
			return;
		}
	}
}

void Board::VerifyIfAnyPlayerHaveAColumnComplete(const uint16_t& column, const bool& isPlayerTwo)
{
	uint8_t downLimit = isPlayerTwo * 20;
	uint8_t upLimit = isPlayerTwo * 20 + 20;

	uint8_t numberOfSameElements = 0;

	for (uint16_t line = 0; line < m_height; line++)
	{
		if (m_board[line * m_width + column] != std::nullopt &&
			m_board[line * m_width + column] > downLimit &&
			m_board[line * m_width + column] < upLimit)
			numberOfSameElements++;
		else
		{
			if (numberOfSameElements >= m_width / 2)
			{
				DeletePlayerColumn(line, column, numberOfSameElements);
				return;
			}
			numberOfSameElements = 0;
		}
		if (numberOfSameElements >= m_width / 2)
		{
			DeletePlayerColumn(line+1, column, numberOfSameElements);
			return;
		}
	}

}

void Board::DeletePlayerLine(const uint16_t& line, const uint16_t& column, const uint8_t& numberOfSameElements)
{
	for (int index = column - numberOfSameElements; index <= column; index++)
		DeleteAndReplaceElement(line, index);
}

void Board::DeletePlayerColumn(const uint16_t& line, const uint16_t& column, const uint8_t& numberOfSameElements)
{
	for (int index = line - numberOfSameElements; index <= line; index++)
		m_board[index * m_width + column] = std::nullopt;
}
