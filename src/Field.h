#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class Field
{
public:
	Field();
	void draw(sf::RenderTarget & target);
	void setPosition(sf::Vector2f pos);
private:
	void forEachGridCell(std::function<void(size_t, size_t)> func);
	static const size_t ROWS = 10;
	static const size_t COLUMNS = 20;
	static const float thickness;
	sf::RectangleShape m_Frame;

	sf::RectangleShape m_Grid[ROWS][COLUMNS];
};

extern size_t cellSize;