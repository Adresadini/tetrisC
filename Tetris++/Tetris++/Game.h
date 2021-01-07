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
	Game(const uint16_t& width, const uint16_t& height, const bool& multiPlayer, std::string filename);
	void Run();
	void VisualInterface();
	void DisplayBoard(sf::RenderWindow& window);
public:
	const float sizeOfBlockLine = 35.f;

private:
	RandomSquare* m_square;
	Board m_board;
	PieceTypes m_types;
	bool m_gameOver;
	TetrisPiece* m_currentPiece;
	BlackHole m_hole;
	Scores m_scores;
	uint8_t m_speed = 250;
	
private:
	const Board::Position POS = { -2,1 };
private:
	void CheckTopLine();
};

