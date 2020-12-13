#pragma once
#include <iostream>

#include "TetrisPiece.h"

class Player
{
public:
	Player(const std::string& name = NULL, const uint16_t& score = 0, const bool isPlayerTwo = false);

	std::string PlayerToString() const;

	void ModifyScoreInfo();
	uint16_t GetHighScore() const;
	uint16_t GetAverageScore() const;
	uint16_t GetScore() const;
	void SetScore(const uint16_t& score);
	std::string GetName() const;
	void SetName(const std::string& name);

	void MovePiece(TetrisPiece& piece, Board& board, bool gameOver);

private:
	std::string m_name;
	uint16_t m_score;
	uint16_t m_highScore;
	uint16_t m_averageScore;
	uint8_t m_scoreCount;
	std::string m_playerControls;
};