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
	Board(const uint16_t& width,const uint16_t& height,const bool& multiPlayer);

	const std::optional<uint8_t>& operator[] (const Position& pos) const;
	std::optional<uint8_t>& operator[] (const Position& pos);

	size_t GetWidth() const;
	size_t GetHeight() const;

	bool VerifyIfLineIsComplete(const uint16_t& line) const;

	void DeleteAndReplaceLine(const uint16_t& line);
	void DeleteAndReplaceElement(const uint16_t& line, const uint16_t& column);

	uint8_t VerifyIfAnyPlayerHaveALineComplete(const uint16_t& line, const bool& isPlayerTwo) ;
	uint8_t VerifyIfAnyPlayerHaveAColumnComplete(const uint16_t& column, const bool& isPlayerTwo);

	void DeletePlayerLine(const uint16_t& line, const uint16_t& column, const uint8_t& numberOfSameElements);
	void DeletePlayerColumn(const uint16_t& line, const uint16_t& column, const uint8_t& numberOfSameElements);
private:
	size_t m_width;
	size_t m_height;
	size_t m_size;

private:
	std::vector<std::optional<uint8_t>>m_board;
};