#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.h"
#include "BlackHole.h"
#include "Player.h"
#include "TetrisPiece.h"
#include "Scores.h"
#include "PieceTypes.h"
#include "RandomSquare.h"
#include <fstream>
#include <windows.h>
#include <chrono>
class Game
{
public:
	Game(std::string filename);
	void ShowMenu();
public:
	const float sizeOfBlockLine = 35.f;

private:
	PieceTypes m_types;
	bool m_gameOver = false;
	BlackHole m_hole;
	Scores m_scores;
	uint16_t m_level = 0;
	Board::Position m_startPositionPlayer2;

	sf::Sound m_sound;
private:
	void DisplayBoard(sf::RenderWindow& window, const Board& board) const;

	void SingleplayerLogic(const std::string& playerName, const int& m_width, const int& m_height);
	void MultiplayerTeamLogic(const std::string& player1Name, const std::string& player2Name, const int& boardWidth, const int& boardHeight);
	void MultiplayerVersusLogic(const std::string& player1Name, const std::string& player2Name, const int& boardWidth, const int& boardHeight);

	void ShowSinglePlayerSettings(sf::RenderWindow& window, const sf::Font& font);
	void ShowMultiPlayerSettings(sf::RenderWindow& window, const sf::Font& font);

	void CheckTopLine(const Board& board, const bool& isPlayer1);
	void UpdatePlayerInfo(Player& player);

	void ShowGameOver(const Player& player1);
	void ShowGameOverMulTiplayerVersus(const Player& player1, const Player& player2, const bool& isPlayerTwo);
	void ShowTopScores();
};

