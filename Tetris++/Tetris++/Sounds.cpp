#include "Sounds.h"

/*Sounds::Sounds() {
    InitMusic();
}

Sounds::~Sounds() {
    m_sounds.clear();
    m_soundBuffers.clear();
}
/*
void Sounds::InitMusic() {
    m_backgroundTheme.openFromFile(Audio::GAME_THEME);
    m_backgroundTheme.setLoop(true);
}

void Sounds::StopMusic() {
    m_backgroundTheme.stop();
}

void Sounds::PlayMusic() {
    sf::SoundSource::Status status = m_backgroundTheme.getStatus();
    if (status != sf::SoundSource::Status::Playing) {
        m_backgroundTheme.play();
    }
}

void Sounds::ChangeMusicState() {
    sf::SoundSource::Status status = m_backgroundTheme.getStatus();
    if (status == sf::SoundSource::Status::Stopped) {
        PlayMusic();

    }
    else {
        StopMusic();
    }
}

void Sounds::AddSound(const std::string& key) {
    sf::SoundBuffer buffer;
    buffer.loadFromFile(key);
    m_soundBuffers[key] = buffer;

    sf::Sound sound(m_soundBuffers.at(key));
    m_sounds[key] = sound;
}

void Sounds::PlaySound(const std::string& key) {
    sf::Sound& sound = m_sounds.at(key);
    sound.play();
}

bool Sounds::IsPlaying(const std::string& key) {
    const sf::Sound& sound = m_sounds.at(key);
    return (sound.getStatus() == sf::SoundSource::Status::Playing);
}

void Sounds::StopSound(const std::string& key) {
    sf::Sound& sound = m_sounds.at(key);
    if (sound.getStatus() == sf::SoundSource::Status::Playing) {
        sound.stop();
    }
}*/