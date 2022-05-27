#include "Scores.h"

void Scores::ReadPlayers(const std::string& fileName)
{
	std::ifstream file(fileName);

	while (!file.eof())
	{
		Player player("", false);
		file >> player;
		if (player.GetName() != "")
			m_scores.push_back(player);
	}
}

void Scores::PrintPlayers(const std::string& fileName)
{
	std::ofstream file;
	file.open("Scores.txt", std::ofstream::out | std::ofstream::trunc);
	for (auto& player : m_scores)
	{
		file << player;
		file << std::endl;
	}
}

void Scores::GetPlayer(Player& newPlayer)
{
	auto player = std::find(m_scores.begin(), m_scores.end(), newPlayer);
	if (player == m_scores.end())
		m_scores.push_back(newPlayer);
	else
		newPlayer.SetInfo(player->GetHighScore(), player->GetAverageScore(), player->GetScoreCount());
}

void Scores::UpdatePlayer(const Player& player)
{
	auto foundPlayer = std::find(m_scores.begin(), m_scores.end(), player);
	m_scores.erase(foundPlayer);
	m_scores.push_back(player);
	std::sort(m_scores.begin(), m_scores.end());
}

std::vector<Player> Scores::GetScores()
{
	return m_scores;
}
