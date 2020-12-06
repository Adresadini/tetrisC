#include "Scores.h"

std::multimap<uint16_t, std::string> invert(std::map<std::string, uint16_t> &m_map)
{
    std::multimap<uint16_t, std::string> multiMap;
    
    std::map<std::string, uint16_t> ::iterator index;
    for (index = m_map.begin(); index != m_map.end(); index++)
    {
        multiMap.insert(std::make_pair(index->second, index->first));
    }

    return multiMap;
}

std::ostream& operator<<(std::ostream& out, Scores& playerInfo)
{
    for (auto &index : playerInfo.m_map)
        out << index.first << " " << index.second << std::endl;
    return out;
}

void Scores::ReadPlayers(std::string fileName)
{
    std::ifstream file(fileName);
    while (!file.eof())
    {
        std::string name;
        uint16_t score;
        file >> name;
        file >> score;
        m_map.insert(std::make_pair(name, score));
    }
}

void Scores::PrintPlayers(std::string& fileName)
{
}

bool Scores::IsNewPlayer(Player& newPlayer)
{
    for (auto index: m_map)
    {
        if (newPlayer.GetName() == index.first)
            return false;
    }
    m_map.insert(std::make_pair(newPlayer.GetName(),newPlayer.GetScore()));
    return true;
}