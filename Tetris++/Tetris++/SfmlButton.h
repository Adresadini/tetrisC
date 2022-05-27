#pragma once
#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>

class SfmlButton
{
	enum class ButtonStates
	{
		BTN_IDLE = 0,
		BTN_HOVER,
		BTN_ACTIVE
	};
private:
	ButtonStates m_buttonState;

	sf::RectangleShape m_shape;
	sf::Font m_font;
	sf::Text m_text;
	sf::Color m_idleColor;
	sf::Color m_activeColor;
	sf::Color m_hoverColor;
public:
	SfmlButton(float x, float y, float width, float height,
		sf::Font, std::string, sf::Color, sf::Color, sf::Color);
	void Update(const sf::Vector2f&);
	void Render(sf::RenderWindow& target) const;
	const bool IsPressed() const;
};

