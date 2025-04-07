#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

constexpr size_t ROWS = 10;
constexpr size_t COLUMNS = 20;

const float thicknessFrame = 5.f;

class Field
{
public:
	Field();
	void draw(sf::RenderTarget & target);
	void setPosition(sf::Vector2f pos);
private:
	void forEachGridCell(std::function<void(size_t, size_t)> func);
	sf::RectangleShape m_Frame;

	sf::RectangleShape m_Grid[ROWS][COLUMNS];
};

extern size_t cellSize;