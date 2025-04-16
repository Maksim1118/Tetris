#pragma once
#include "Button.h"

class ToogleButton : public Button
{
public:
	ToogleButton(sf::Texture& normal, sf::Texture& pressed);
	void updateState(const sf::Vector2f mousePos);
};