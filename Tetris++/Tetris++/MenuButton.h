#pragma once
#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "ButtonState.h"

#include <array>

class MenuButton {
public:
    explicit MenuButton(sf::Texture& texture);
    virtual ~MenuButton();

    void AddSprite(sf::IntRect intRet, ButtonState state);
    void Draw(sf::RenderWindow& window);
    bool IsClicked(sf::RenderWindow& window);
    void SetPosition(sf::Vector2f position);

private:
    static const int m_numberOfStates = 2;

    std::array< sf::Sprite, m_numberOfStates > m_sprites;
    ButtonState m_state;
    sf::Texture& m_texture;
    sf::Vector2f m_position;

    bool IsHoovered(sf::RenderWindow& window);
};
#endif
