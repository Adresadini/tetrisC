#pragma once
#include <iostream>

#include "TetrisPiece.h"

class Player
{
public:
	Player(std::string name = NULL, uint16_t score = 0);

	std::string PlayerToString() const;
	
	void ModifyScoreInfo();
	uint16_t GetHighScore() const;
	uint16_t GetAverageScore() const;
	uint16_t GetScore() const;
	void SetScore(uint16_t& score);
	std::string GetName() const;
	void SetName(std::string& name);

	void MoveLeft(TetrisPiece& piece);
	void MoveRight(TetrisPiece& piece);

private:
	std::string m_name;
	uint16_t m_score;
	uint16_t m_highScore;
	uint16_t m_averageScore;
	uint8_t m_scoreCount;

};