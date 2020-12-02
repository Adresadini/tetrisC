#pragma once
#include <optional>
#include <iostream>
#include <array>
#include <vector>
class Board
{
public:
	using Position = std::pair<int16_t, int16_t>;

public:
	Board(uint16_t width,uint16_t height,bool multiPlayer);

	const std::optional<uint8_t>& operator[] (const Position& pos) const;
	std::optional<uint8_t>& operator[] (const Position& pos);

	friend std::ostream& operator << (std::ostream&, const Board&);

	size_t getWidth() const;
	size_t getHeight() const;
	void DeleteCompleteLines();
private:
	size_t m_width;
	size_t m_height;
	size_t m_size;

private:
	std::vector<std::optional<uint8_t>>m_board;
public:
	bool VerifyIfLineIsComplete(uint16_t line);
	void DeleteAndReplaceLine(uint16_t line);
};