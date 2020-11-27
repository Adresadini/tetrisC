#pragma once
#include <array>
#include <iostream>
#include <optional>
#include "Board.h"
class TetrisPiece
{
public:
	TetrisPiece(uint8_t, uint8_t,uint8_t);

	void MoveLeft();
	void MoveDown(const Board);
	void MoveRight(const Board);

	void Draw(Board&);
	void Delete(Board&);

private:
	uint8_t m_positionX;
	uint8_t m_positionY;

private:
	static const size_t kWidth = 4;
	static const size_t kHeight = 4;
	static const size_t kSize = kWidth * kHeight;
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> m_piece;

private:
	static const size_t NumberOfPieces = 7;
	static const size_t PiecesSize = 4;
	std::array<std::array<uint8_t, PiecesSize>, NumberOfPieces> m_pieceType = { {
		{1, 5, 9, 13},
		{0, 1, 5, 6},
		{1, 2, 4, 5},
		{0, 4, 8, 9},
		{1, 5, 8, 9},
		{0, 1, 4, 5},
		{0, 1, 2, 5} } };
	};

