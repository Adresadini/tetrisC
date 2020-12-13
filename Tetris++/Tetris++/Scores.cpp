#include "Scores.h"

std::multimap<uint16_t, Player, std::greater<uint16_t>> invert(std::map<Player, uint16_t> &m_map)
{
    std::multimap<uint16_t, Player, std::greater<uint16_t>> multiMap;
    
    std::map<Player, uint16_t> ::iterator index;
    for (index = m_map.begin(); index != m_map.end(); index++)
    {
        multiMap.insert(std::make_pair(index->second, index->first));
    }

    return multiMap;
}

std::ostream& operator<<(std::ostream& out, Scores& playerInfo)
{
    std::multimap<uint16_t, Player, std::greater<uint16_t>> newMap = invert(playerInfo.m_map);
    std::multimap<uint16_t, Player>::iterator index;
    for (index = newMap.begin(); index != newMap.end(); index++)
    {
        out << index->second << " " << index->first << std::endl;
    }
    return out;
}

void Scores::ReadPlayers(const std::string& fileName)
{
    std::ifstream file(fileName);
    while (!file.eof())
    {
        std::string name;
        uint16_t highScore;
        file >> name;
        file >> highScore;
        m_map.insert(std::make_pair(name, highScore));
    }
}

void Scores::PrintPlayers(const std::string& fileName)
{
    std::ofstream file(fileName);
    file.open("Scores.txt", std::ios_base::app);
    std::multimap<uint16_t, Player, std::greater<uint16_t>> newMap = invert(m_map);
    std::multimap<uint16_t, Player>::iterator index;
    for (index = newMap.begin(); index != newMap.end(); index++)
    {
        file << index->second <<" "<< index->first << std::endl;
    }
}

bool Scores::IsNewPlayer(const Player& newPlayer)
{
    for (auto &index: m_map)
    {
        if (newPlayer.GetName() == index.first.GetName())
            return false;
    }
    m_map.insert(std::make_pair(newPlayer.GetName(), newPlayer.GetScore()));
    return true;
}