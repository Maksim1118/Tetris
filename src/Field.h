#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <array>

#include "Colors.h"

constexpr size_t ROWS = 10;
constexpr size_t COLUMNS = 20;

const float thicknessFrame = 5.f;

using Grid = std::array<std::array<sf::RectangleShape, COLUMNS>, ROWS>;

class Field
{
public:
	Field();
	void draw(sf::RenderTarget & target);
	void setPosition(sf::Vector2f pos);
	bool isCollision(size_t row, size_t column);
	bool isCellEmpty(size_t row, size_t column);
	Grid & getGrid();
private:
	void forEachGridCell(std::function<void(size_t, size_t)> func);
	sf::RectangleShape m_Frame;

	Grid m_Grid;
	Colors m_Colors;
};

extern size_t cellSize;