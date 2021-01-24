#include "TextureManager.h"

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() {
    m_textures.clear();
}

void TextureManager::AddTexture(const std::string & key) {
    sf::Image image;
    image.loadFromFile(key);

    sf::Texture texture;
    texture.loadFromImage(image);
    m_textures[key] = texture;
}

sf::Texture& TextureManager::GetTexture(const std::string & key) {
    return m_textures.at(key);
}