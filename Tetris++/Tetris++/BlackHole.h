#pragma once
#include "Board.h"
class BlackHole
{
public:
	BlackHole() = default;
	void Spawn(Board& board);
	void Disappear(Board& board) const;
private:
	Board::Position m_spawnPosition;

private:
	//bool FoundAPiece(const  Board& board, TetrisPiece& piece) const;
};