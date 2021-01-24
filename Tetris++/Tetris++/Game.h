#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "BlackHole.h"
#include "Player.h"
#include "TetrisPiece.h"
#include "Scores.h"
#include "PieceTypes.h"
#include "RandomSquare.h"
#include <fstream>
#include <windows.h>
class Game
{
public:
	Game(const uint16_t& width, const uint16_t& height, std::string filename);
	void VisualInterface();
	void DisplayBoard(sf::RenderWindow& window, Board& board);
	void SingleplayerLogic();
	void MultiplayerTeamLogic();
	void MultiplayerVersusLogic();
	void ShowMenu();
public:
	const float sizeOfBlockLine = 35.f;

private:
	PieceTypes m_types;
	bool m_gameOver;
	BlackHole m_hole;
	Scores m_scores;
	uint16_t m_level = 0;
	Board::Position m_startPositionPlayer2;

	uint16_t m_boardWidth;
	uint16_t m_boardHeight;

private:
	void CheckTopLine(Board& board);
};

