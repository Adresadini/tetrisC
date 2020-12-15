#pragma once
#include "Board.h"
#include "BlackHole.h"
#include "Player.h"
#include "TetrisPiece.h"
#include "Scores.h"
#include "PieceTypes.h"
#include <fstream>
#include <windows.h>
class Game
{
public:
	Game(const uint16_t& width, const uint16_t& height, const bool& multiPlayer, std::string filename);
	void Run();
private:
	Board m_board;
	PieceTypes m_types;
	bool m_gameOver;
	TetrisPiece* m_CurrentPiece;
	BlackHole m_hole;
	Scores m_scores;
private:
	const Board::Position POS = { -2,1 };
};

