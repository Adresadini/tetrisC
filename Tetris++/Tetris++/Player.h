#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TetrisPiece.h"

class Player
{
public:
	Player(const std::string& name = NULL, const bool isPlayerTwo = false);

	std::string PlayerToString() const;

	void ModifyScoreInfo();
	uint16_t GetHighScore() const;
	uint16_t GetAverageScore() const;
	uint16_t GetScoreCount() const;
	uint16_t GetScore() const;
	void AddScore(const uint16_t& score);
	std::string GetName() const;
	void SetInfo(const uint16_t& highScore, const uint16_t& averageScore, const uint16_t& scoreCount);

	void InitKeyBindings(bool isPlayerTwo);
	void MovePiece(const sf::Event& event, TetrisPiece& piece, Board& board);
	friend std::ostream& operator <<(std::ostream&, const Player&);
	friend std::istream& operator >>(std::istream&, Player&);
	bool operator ==(Player player);
	bool operator <(const Player&)const;

private:
	std::string m_name;
	uint16_t m_score = 0;
	uint16_t m_highScore=0;
	uint16_t m_averageScore=0;
	uint16_t m_scoreCount=0;
private:
	static const size_t NumberOfInputs = 7;
	std::array<sf::Keyboard::Key, NumberOfInputs>m_input;

};