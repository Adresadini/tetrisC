#include "Scores.h"

std::istream& operator>>(std::istream& in, std::priority_queue<Player>& queue)
{

    return in;
}

std::ostream& operator<<(std::ostream& out, Scores& playerInfo)
{
    for (Player index : playerInfo.m_vector)
        out << index.GetName() << " " << index.GetScore() << std::endl;
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
        m_vector.emplace_back(Player(name, score));
    }
    std::sort(m_vector.begin(), m_vector.end(), comparePlayers);
}

bool Scores::IsNewPlayer(Player& newPlayer)
{
    for (auto index: m_vector)
    {
        if (newPlayer.GetName() == index.GetName())
            return false;
    }
    m_vector.emplace_back(Player(newPlayer));
    return true;
}