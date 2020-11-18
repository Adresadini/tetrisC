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

	const std::optional<uint16_t>& operator[] (const Position& pos) const;
	std::optional<int>& operator[] (const Position& pos);

	friend std::ostream& operator << (std::ostream&, const Board&);

private:
	size_t m_width;
	size_t m_height;
	size_t m_size;

private:
	std::vector<std::optional<int>>m_board;
};

