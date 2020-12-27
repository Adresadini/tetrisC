#include "Scores.h"

void Scores::ReadPlayers(const std::string& fileName, Player player)
{
	std::ifstream file(fileName);
	while (!file.eof())
	{
		file >> player;
		m_set.insert(player);
	}
}

void Scores::PrintPlayers(const std::string& fileName)
{
	std::ofstream file;
	file.open("Scores.txt", std::ios_base::app);
	std::set<Player, std::greater<Player>>::iterator index;
	for (index = m_set.begin(); index != m_set.end(); index++)
	{
		file << *index;
		file << std::endl;
	}
}

bool Scores::IsNewPlayer(const Player& newPlayer)
{
	if (m_set.find(newPlayer.GetName()) == m_set.end())
	{
		m_set.insert(newPlayer);
		return true;
	}
	return false;
}
