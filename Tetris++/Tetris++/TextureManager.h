#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <map>
#include <string>

#include "SoundManage.h"

class TextureManager {
private:
    std::map< std::string, sf::Texture > m_textures;

public:
    TextureManager();
    virtual ~TextureManager();

    void AddTexture(const std::string& key);
    sf::Texture& GetTexture(const std::string& key);
};

#endif