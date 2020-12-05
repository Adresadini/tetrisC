#pragma once
#include <array>
#include <iostream>
#include <optional>

#include "Board.h"
#include "PieceTypes.h"

class TetrisPiece
{
public:
	TetrisPiece(const Board::Position&, const PieceTypes&);

	void MoveLeft(Board&);
	void MoveDown(Board&);
	void MoveRight(Board&);

	void RotateLeft(Board&);
	void RotateRight(Board&);

	void Draw(Board&) const;
	void Delete(Board&) const;

	size_t GetKHeight() const;
	size_t GetKWidth() const;
	Board::Position GetPosition() const;

	bool IsSet() const;

	void movePiece(Board& board, bool GameOver);
	void resetPieceElement(uint16_t position);
private:
	Board::Position m_position;
	bool set = false;

private:
	static const size_t kWidth = 4;
	static const size_t kHeight = 4;
	static const size_t kSize = kWidth * kHeight;
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> m_piece;
};
