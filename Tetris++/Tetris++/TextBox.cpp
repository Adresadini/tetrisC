#include "TextBox.h"

TextBox::TextBox(float x, float y, float width, float height,
	sf::Font font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	:m_font(font), m_idleColor(idleColor), m_hoverColor(hoverColor), m_activeColor(activeColor)
{
	m_buttonState = TextBox::TextBoxStates::BTN_IDLE;

	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setSize(sf::Vector2f(width, height));


	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(28);
	m_text.setPosition(
		m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f) - m_text.getGlobalBounds().width / 2.f,
		m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f) - m_text.getGlobalBounds().height / 2.f
	);

	m_shape.setFillColor(m_idleColor);
}

void TextBox::Update(const sf::Vector2f& mousePos)
{
	m_buttonState = TextBox::TextBoxStates::BTN_IDLE;
	if (m_shape.getGlobalBounds().contains(mousePos) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_buttonState = TextBox::TextBoxStates::BTN_ACTIVE;
		m_isSelected = true;
	}

	switch (m_buttonState)
	{
	case TextBox::TextBoxStates::BTN_IDLE:
		m_shape.setFillColor(m_idleColor);
		break;
	case TextBox::TextBoxStates::BTN_ACTIVE:
		m_shape.setFillColor(m_activeColor);
		break;
	default:
		m_shape.setFillColor(sf::Color::Red);
		break;
	}

}

void TextBox::Render(sf::RenderWindow& target) const
{
	target.draw(m_shape);
	target.draw(m_text);
}

const bool TextBox::IsPressed() const
{
	if (m_buttonState == TextBox::TextBoxStates::BTN_ACTIVE)
		return true;
	return false;
}

void TextBox::UpdateText(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		if (!m_text.getString().isEmpty())
			m_text.setString(m_text.getString().substring(0, m_text.getString().getSize() - 1));
		return;
	}


	if (static_cast<char>(event.text.unicode + 65) >= 65
		&& static_cast<char>(event.text.unicode + 65) <= 90
		&& m_text.getString().getSize() < 17)  //TO DO:: Modifica sa nu mai fie 17, sa fie mai modular
		m_text.setString(m_text.getString() + static_cast<char>(static_cast<char>(event.text.unicode + 65)));


	if (static_cast<char>(event.text.unicode + 22) >= 48
		&& static_cast<char>(event.text.unicode + 22) <= 57
		&& m_text.getString().getSize() < 17)
		m_text.setString(m_text.getString() + static_cast<char>(static_cast<char>(event.text.unicode + 22)));

	m_text.setPosition(
		m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f) - m_text.getGlobalBounds().width / 2.f,
		m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f) - m_text.getGlobalBounds().height / 2.f
	);
}

void TextBox::SetIsSelected(bool isSelected)
{
	m_isSelected = isSelected;
}

bool TextBox::GetIsSelected()
{
	return m_isSelected;
}

