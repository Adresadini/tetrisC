#pragma once
#include <array>
#include <iostream>
#include <optional>
#include "Board.h"
class TetrisPiece
{
public:
	TetrisPiece(Board::Position,uint8_t);

	void MoveLeft(Board&);
	void MoveDown(Board&);
	void MoveRight(Board&);

	void RotateLeft(Board&);
	void RotateRight(Board&);

	void Draw(Board&);
	void Delete(Board&);

private:
	Board::Position m_position;

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

