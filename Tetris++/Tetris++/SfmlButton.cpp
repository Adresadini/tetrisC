#include "SfmlButton.h"

SfmlButton::SfmlButton(float x, float y, float width, float height,
	sf::Font font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	:m_font(font), m_idleColor(idleColor), m_hoverColor(hoverColor), m_activeColor(activeColor)
{
	m_buttonState = SfmlButton::ButtonStates::BTN_IDLE;

	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setSize(sf::Vector2f(width, height));


	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(28);
	m_text.setPosition(
		m_shape.getPosition().x +(m_shape.getGlobalBounds().width / 2.f)- m_text.getGlobalBounds().width / 2.f,
		m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f) - m_text.getGlobalBounds().height / 2.f
	);

	m_shape.setFillColor(m_idleColor);
}

SfmlButton::~SfmlButton()
{

}

void SfmlButton::Update(sf::Vector2f mousePos)
{
	m_buttonState = SfmlButton::ButtonStates::BTN_IDLE;
	if (m_shape.getGlobalBounds().contains(mousePos))
	{
		m_buttonState = SfmlButton::ButtonStates::BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_buttonState = SfmlButton::ButtonStates::BTN_ACTIVE;
		}
	}

	switch (m_buttonState)
	{
	case SfmlButton::ButtonStates::BTN_IDLE:
		m_shape.setFillColor(m_idleColor);
		break;
	case SfmlButton::ButtonStates::BTN_HOVER:
		m_shape.setFillColor(m_hoverColor);
		break;
	case SfmlButton::ButtonStates::BTN_ACTIVE:
		m_shape.setFillColor(m_activeColor);
		break;
	default:
		m_shape.setFillColor(sf::Color::Red);
		break;
	}

}

void SfmlButton::Render(sf::RenderWindow& target)
{
	target.draw(m_shape);
	target.draw(m_text);
}

const bool SfmlButton::isPressed() const
{
	if (m_buttonState == SfmlButton::ButtonStates::BTN_ACTIVE)
		return true;
	return false;
}
