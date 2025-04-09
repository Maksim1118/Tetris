#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <array>

#include "Colors.h"

constexpr size_t ROWS = 12;
constexpr size_t COLUMNS = 24;

const sf::Vector2f startPos = sf::Vector2f(520.f, 60.f);

using Grid = std::array<std::array<sf::RectangleShape, COLUMNS>, ROWS>;

class Field
{
public:
	Field();
	void resetColorGrid();
	void draw(sf::RenderTarget & target);
	void setPosition(sf::Vector2f pos);
	bool isCollision(int row, int column);
	bool isCellEmpty(int row, int column);
	Grid & getGrid();
	void clearFullRows();
private:
	bool isRowFull(size_t column);
	void clearRow(size_t column);
	void moveRowDown(size_t column, size_t numColumn);

	void forEachGridCell(std::function<void(size_t, size_t)> func);
	sf::RectangleShape m_Frame;

	Grid m_Grid;
	Colors m_Colors;
};

extern size_t cellSize;