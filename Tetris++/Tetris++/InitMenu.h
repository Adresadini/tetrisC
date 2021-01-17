#ifndef INITMENU_H
#define INITMENU_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "TextureManager.h"
#include "Audio.h"
#include "Texture.h"
#include "SoundManage.h"

class InitMenu {
public:
    InitMenu();
    virtual ~InitMenu();

    void SetExitGame();
    TextureManager& GetTextureManager();
    SoundManage& GetSounds();
    sf::RenderWindow& GetWindow();
    bool IsExitGame();

private:
    const int WIDTH = 1200;
    const int HEIGHT = 800;
    const int FPS = 30;

    bool m_exitGame;
    sf::RenderWindow m_window;
    TextureManager m_textureManager;
    SoundManage m_sounds;

    void CreateWindow();
    void LoadSounds();
    void LoadTextures();
};

#endif