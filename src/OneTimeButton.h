#pragma once
#include "Button.h"

class OneTimeButton : public Button
{
public:
	OneTimeButton(sf::Texture& normal, sf::Texture& pressed);
	void updateState(const sf::Vector2f mousePos);
};