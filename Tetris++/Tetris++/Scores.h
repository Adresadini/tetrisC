#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Player.h"

class Scores
{
public:

	Scores() = default;

	void ReadPlayers(const std::string& fileName);
	void PrintPlayers(const std::string& fileName);

	void GetPlayer(Player&);
	void UpdatePlayer(const Player&);
	std::vector<Player> GetScores();
private:

	std::vector<Player> m_scores;
};