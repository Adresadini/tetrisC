#pragma once
#include "Board.h"
#include "TetrisPiece.h"
class BlackHole
{
public:
	BlackHole() = default;
	void Spawn(Board& board, TetrisPiece& tetrisPiece);
	void Disappear(Board& board) const;
	void EatPiece(Board& board, TetrisPiece& piece) const;

private:
	Board::Position m_spawnPosition;

private:
	bool FoundAPiece(const  Board& board, TetrisPiece& piece) const;
};