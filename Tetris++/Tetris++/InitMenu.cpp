#include "InitMenu.h"

InitMenu::InitMenu() 
{
    m_exitGame = false;

    CreateWindow();
    LoadSounds();
    LoadTextures();
}

//InitMenu::~InitMenu() = default;

sf::RenderWindow& InitMenu::GetWindow() 
{
    return m_window;
};

TextureManager& InitMenu::GetTextureManager() 
{
    return m_textureManager;
};

void InitMenu::SetExitGame() 
{
    m_exitGame = true;
}

bool InitMenu::IsExitGame()
{
    return m_exitGame;
}

void InitMenu::LoadSounds() 
{
    //m_sounds.AddSound(Audio::GAME_THEME);
    //m_sounds.AddSound(Audio::EAT);
    //m_sounds.AddSound(Audio::END);
}

void InitMenu::LoadTextures() 
{
    //m_textureManager.AddTexture(Texture::SFML_LOGO);
    m_textureManager.AddTexture(Texture::MAIN_MENU_BACKGROUND);
    m_textureManager.AddTexture(Texture::MAIN_MENU_BUTTONS);
    //m_textureManager.AddTexture(Texture::MAIN_GAME_TEXTURES);
    //m_textureManager.AddTexture(Texture::SCORE_TEXTURES);
    m_textureManager.AddTexture(Texture::GAME_OVER);
    m_textureManager.AddTexture(Texture::VICTORY);
}

void InitMenu::CreateWindow() 
{
    m_window.create(sf::VideoMode(WIDTH, HEIGHT), "@SFMLTetris_VERSION1");
    m_window.setFramerateLimit(FPS);
    m_window.setKeyRepeatEnabled(false);
}

SoundManage& InitMenu::GetSounds() 
{
    return m_sounds;
};