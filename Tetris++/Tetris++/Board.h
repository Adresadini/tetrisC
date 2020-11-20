#pragma once
#include <optional>
#include <iostream>
#include <array>
#include <vector>
class Board
{
public:
	using Position = std::pair<uint16_t, uint16_t>;

public:
	Board(uint16_t width,uint16_t height,bool multiPlayer);

	const std::optional<uint8_t>& operator[] (const Position& pos) const;
	std::optional<uint8_t>& operator[] (const Position& pos);

	friend std::ostream& operator << (std::ostream&, const Board&);

	size_t getWidth();
	size_t getHeight();
private:
	size_t m_width;
	size_t m_height;
	size_t m_size;

private:
	std::vector<std::optional<uint8_t>>m_board;
};

