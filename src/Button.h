#pragma once
#include <SFML/Graphics.hpp>

enum class ButtonState
{
	IDLE,
	PRESSED,
	RELEASED
};

class Button
{
public:
	Button(sf::Texture& normal, sf::Texture& pressed);
	virtual ~Button() = default;
	virtual void updateState(const sf::Vector2f mousePos) = 0;
	void setPosition(sf::Vector2f pos);
	void draw(sf::RenderTarget& window);
	void setScale(float scale);
	bool isPressed();
protected:
	bool isPos(const sf::Vector2f mousPos);
	void switchTexture();
	ButtonState m_State;
	bool m_isNormalState;
	sf::Texture& m_Normal;
	sf::Texture& m_Pressed;
	sf::Sprite m_CurrentSprite;
};