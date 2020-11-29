#pragma once
#include <iostream>

class Player
{
public:
	Player(std::string name = NULL, uint16_t score = 0);

	std::string PlayerToString();
	
	void ModifyScoreInfo();
	uint16_t GetHighScore();
	uint16_t GetAverageScore();
	uint16_t GetScore();
	std::string GetName();


private:
	std::string m_name;
	uint16_t m_score;
	static uint16_t m_highScore;
	static uint16_t m_averageScore;
	static uint8_t m_scoreCount;

};

