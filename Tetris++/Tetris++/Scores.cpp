#include "Scores.h"

void Scores::ReadPlayers(const std::string& fileName)
{
	std::ifstream file(fileName);
	
	while (!file.eof())
	{
		Player player("Player1",false);
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

void Scores::GetPlayer(Player& newPlayer)
{
	std::set<Player>::iterator player;
	player = m_set.find(newPlayer);
	if (player == m_set.end())
		m_set.insert(newPlayer);
	else
		newPlayer = *player;
}

void Scores::UpdatePlayer(const Player& player)
{
	m_set.erase(m_set.find(player));
	m_set.insert(player);
}
