#ifndef SOUNDMANAGE_H
#define SOUNDMANAGE_H

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <string>
#include <map>

#include "Audio.h"

class SoundManage {
public:
    SoundManage();
    virtual ~SoundManage();

    void AddSound(const std::string& key);
    bool IsPlaying(const std::string& key);
    void StopSound(const std::string& key);
    void PlaySound(const std::string& key);

    void PlayMusic();
    void ChangeMusicState();

private:
    std::map< std::string, sf::SoundBuffer > m_soundBuffers;
    std::map< std::string, sf::Sound > m_sounds;
    sf::Music m_backgroundTheme;

    void InitMusic();
    void StopMusic();
};


#endif