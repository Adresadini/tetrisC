#include "Scores.h"

std::ostream& operator<<(std::ostream& out, Scores& playerInfo)
{
    for (auto &index : playerInfo.m_map)
        out << index.first << " " << index.second << std::endl;
    return out;
}

bool comparePlayers(Player p1, Player p2)
{
    return (p1.GetScore() > p2.GetScore());
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