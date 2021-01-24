#include "MenuButton.h"

MenuButton::MenuButton(sf::Texture& texture) 
    : m_texture(texture) 
{
    m_state = ButtonState::NORMAL;
}

MenuButton::~MenuButton() = default;

void MenuButton::AddSprite(sf::IntRect intRet, ButtonState state) 
{
    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setTextureRect(intRet);
    m_sprites[state] = sprite;
}

void MenuButton::SetPosition(sf::Vector2f position) 
{
    this->m_position = position;
}

void MenuButton::Draw(sf::RenderWindow & window) 
{
    sf::Sprite currentSprite = m_sprites[m_state];
    currentSprite.setPosition(m_position);

    if (IsHoovered(window)) 
    {
        m_state = ButtonState::PRESSED;
    }
    else 
    {
        m_state = ButtonState::NORMAL;
    }

    window.draw(currentSprite);
}

bool MenuButton::IsHoovered(sf::RenderWindow & window) {
    sf::Sprite currentSprite = m_sprites[m_state];
    currentSprite.setPosition(m_position);

    sf::FloatRect spriteRect = currentSprite.getGlobalBounds();
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    return spriteRect.contains(mousePos);
}

bool MenuButton::IsClicked(sf::RenderWindow & window) {
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    return (mousePressed && IsHoovered(window));
}