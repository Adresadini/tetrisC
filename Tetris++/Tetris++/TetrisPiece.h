#pragma once
#include <array>
#include <iostream>
#include <optional>
#include "Board.h"
#include "PieceTypes.h"
class TetrisPiece
{
public:
	TetrisPiece(Board::Position&,PieceTypes&);

	void MoveLeft(Board&);
	void MoveDown(Board&);
	void MoveRight(Board&);

	void RotateLeft(Board&);
	void RotateRight(Board&);

	void Draw(Board&);
	void Delete(Board&);

	size_t getKHeight();
	size_t getKWidth();
	Board::Position getPosition();
private:
	Board::Position m_position;

private:
	static const size_t kWidth = 4;
	static const size_t kHeight = 4;
	static const size_t kSize = kWidth * kHeight;
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> m_piece;
};
