#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Vector3i defaultColors, sf::Vector3i hoverColors)
{
	button.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));

	button.setFillColor(sf::Color(defaultColors.x, defaultColors.y, defaultColors.z));
	button.setPosition(position);
	button.setSize(size);

	_hoverColors = hoverColors;
	_defaultColors = defaultColors;
}

Button::Button()
{

}

void Button::SetButtonName(const sf::String _buttonName, sf::Font &font, unsigned short fontSize)
{
    buttonName.setString(_buttonName);
    buttonName.setFont(font);
    buttonName.setFillColor(sf::Color::White);
    buttonName.setCharacterSize(fontSize);

	sf::Vector2f buttonPosition = button.getPosition();
	sf::FloatRect textBounds = buttonName.getGlobalBounds();
	buttonName.setOrigin(sf::Vector2f(textBounds.width / 2, textBounds.height / 2));
	buttonName.setPosition(sf::Vector2f(buttonPosition.x, buttonPosition.y-10));
}

bool Button::IsPressed(sf::Vector2i mousePosition)
{
	sf::FloatRect buttonBounds = button.getGlobalBounds();

	if (buttonBounds.contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
		return true;
	return false;
}

void Button::CheckHover(sf::Vector2i mousePosition)
{
	sf::FloatRect buttonBounds = button.getGlobalBounds();

	if (buttonBounds.contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
	{
		button.setFillColor(sf::Color(_hoverColors.x, _hoverColors.y, _hoverColors.z));
	}
	else
	{
		button.setFillColor(sf::Color(_defaultColors.x, _defaultColors.y, _defaultColors.z));
	}

	return;
}
