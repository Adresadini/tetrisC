#pragma once
#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>

class TextBox
{
	enum class TextBoxStates
	{
		BTN_IDLE = 0,
		
		BTN_ACTIVE
	};
private:
	TextBoxStates m_buttonState;

	sf::RectangleShape m_shape;
	sf::Font m_font;
	sf::Text m_text;
	sf::Color m_idleColor;
	sf::Color m_activeColor;
	sf::Color m_hoverColor;
	bool m_isSelected = false;
public:
	TextBox(float x, float y, float width, float height,
		sf::Font, std::string, sf::Color, sf::Color, sf::Color);
	void Update(const sf::Vector2f&);
	void Render(sf::RenderWindow& target) const;
	const bool IsPressed() const;
	void UpdateText(const sf::Event& event, const bool& onlyNumeric);
	void SetIsSelected(bool isSelected);
	bool GetIsSelected();
	std::string GetText();
};

