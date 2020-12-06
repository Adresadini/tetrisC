#include "Scores.h"

std::multimap<uint16_t, std::string, std::greater<uint16_t>> invert(std::map<std::string, uint16_t> &m_map)
{
    std::multimap<uint16_t, std::string, std::greater<uint16_t>> multiMap;
    
    std::map<std::string, uint16_t> ::iterator index;
    for (index = m_map.begin(); index != m_map.end(); index++)
    {
        multiMap.insert(std::make_pair(index->second, index->first));
    }

    return multiMap;
}

std::ostream& operator<<(std::ostream& out, Scores& playerInfo)
{
    std::multimap<uint16_t, std::string, std::greater<uint16_t>> newMap = invert(playerInfo.m_map);
    std::multimap<uint16_t, std::string>::iterator index;
    for (index = newMap.begin(); index != newMap.end(); index++)
    {
        out << index->second << " " << index->first << std::endl;
    }
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

/*void Scores::PrintPlayers(const std::string& fileName)
{
    std::ofstream file(fileName);
    file.open("Scores.txt", std::ofstream::out | std::ofstream::trunc);
    std::multimap<uint16_t, std::string, std::greater<uint16_t>> newMap = invert(m_map);
    std::multimap<uint16_t, std::string>::iterator index;
    for (index = newMap.begin(); index != newMap.end(); index++)
    {
        file << index->second <<" "<< index->first << std::endl;
    }
}*/

bool Scores::IsNewPlayer(Player& newPlayer)
{
    for (auto &index: m_map)
    {
        if (newPlayer.GetName() == index.first)
            return false;
    }
    m_map.insert(std::make_pair(newPlayer.GetName(), newPlayer.GetScore()));
    return true;
}