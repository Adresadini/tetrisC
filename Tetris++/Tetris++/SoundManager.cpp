#include "SoundManager.h"

/*SoundManager::SoundManager() {
    InitMusic();
}

SoundManager::~SoundManager() {
    m_sounds.clear();
    m_soundBuffers.clear();
}

void SoundManager::InitMusic() {
    m_backgroundTheme.openFromFile(Audio::GAME_THEME);
    m_backgroundTheme.setLoop(true);
}

void SoundManager::StopMusic() {
    m_backgroundTheme.stop();
}

void SoundManager::PlayMusic() {
    sf::SoundSource::Status status = m_backgroundTheme.getStatus();
    if (status != sf::SoundSource::Status::Playing) {
        m_backgroundTheme.play();
    }
}

void SoundManager::ChangeMusicState() {
    sf::SoundSource::Status status = m_backgroundTheme.getStatus();
    if (status == sf::SoundSource::Status::Stopped) {
        PlayMusic();

    }
    else {
        StopMusic();
    }
}

void SoundManager::AddSound(const std::string& key) {
    sf::SoundBuffer buffer;
    buffer.loadFromFile(key);
    m_soundBuffers[key] = buffer;

    sf::Sound sound(m_soundBuffers.at(key));
    m_sounds[key] = sound;
}

void SoundManager::PlaySound(const std::string& key) {
    sf::Sound& sound = m_sounds.at(key);
    sound.play();
}

bool SoundManager::IsPlaying(const std::string& key) {
    const sf::Sound& sound = m_sounds.at(key);
    return (sound.getStatus() == sf::SoundSource::Status::Playing);
}

void SoundManager::StopSound(const std::string& key) {
    sf::Sound& sound = m_sounds.at(key);
    if (sound.getStatus() == sf::SoundSource::Status::Playing) {
        sound.stop();
    }
}*/