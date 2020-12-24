#pragma once
#include <SFML/Graphics.hpp>
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
	uint8_t GetScoreCount() const;
	uint16_t GetScore() const;
	void SetScore(const uint16_t& score);
	std::string GetName() const;
	void SetName(const std::string& name);

	void InitKeyBindings(bool isPlayerTwo);
	void MovePiece(TetrisPiece& piece, Board& board, bool gameOver);

	friend std::ostream& operator <<(std::ostream&, Player);
	friend std::istream& operator >>(std::istream&, Player);
	bool operator >(const Player&)const;

private:
	std::string m_name;
	sf::Keyboard::Key* m_input;
	uint16_t m_score;
	uint16_t m_highScore;
	uint16_t m_averageScore;
	uint8_t m_scoreCount;
};