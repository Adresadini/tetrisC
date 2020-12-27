#pragma once
#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "ButtonState.h"
#include "MenuButton.h"
#include "GameState.h"
#include "Game.h"

class StateMainMenu : public GameState {

public:
    explicit StateMainMenu(Game& game);
    ~StateMainMenu() override;

    std::unique_ptr< GameState > nextState;
    std::unique_ptr< GameState > getNextState() override;

private:
    const int m_buttonTextureRows = 2;
    const int m_buttonTextureCells = 2;
    const int m_buttonLocationOffset = 10;

    sf::Sprite m_background;
    Game& m_game;

    MenuButton m_playButton;
    MenuButton m_quitButton;

    void CreateButtons();
    sf::Texture& GetButtonsTexture();
    void PrepareBackground();
};

#endif
