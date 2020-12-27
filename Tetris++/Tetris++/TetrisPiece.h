#pragma once
#include "PieceTypes.h"
#include"Board.h"
#include <array>
#include <iostream>
#include <optional>

class TetrisPiece
{
public:
	TetrisPiece(const Board::Position&, const PieceTypes&);

	void MoveLeft(Board&);
	void MoveDown(Board&);
	void MoveRight(Board&);
	void MovePiece(Board& board, bool& GameOver);

	void RotateLeft(Board&);
	void RotateRight(Board&);
	void Scale(Board&);

	void Draw(Board&);
	void Delete(Board&) const;

	size_t GetKHeight() const;
	size_t GetKWidth() const;
	Board::Position GetPosition() const;

	bool IsSet() const;
	bool IsEmpty() const;
	void DeleteCompleteLines(Board& board);
private:
	Board::Position m_position;
	PieceTypes::scaleType m_scaleType;
	uint8_t pieceType;

private:
	bool m_set = false;
	bool m_vertical = true;
	bool m_scaled = false;

private:
	static const size_t kWidth = 4;
	static const size_t kHeight = 4;
	static const size_t kSize = kWidth * kHeight;
	std::array<std::optional<uint8_t>, TetrisPiece::kSize> m_piece;

private:
	void FillBorders();
	void FixMiddle();
	void ScaleDown();
};
