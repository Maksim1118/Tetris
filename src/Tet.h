#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <array>

#include "Field.h"

enum class RotationState
{
	LEFT, RIGHT, UP, DOWN
};

class Tet
{
public:
	Tet();
	void setPosition(sf::Vector2f pos);
	void draw(sf::RenderTarget& window);
	void move(size_t rows, size_t columns);
protected:
	RotationState m_State;
	unsigned int m_ColorIndex;
};