#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <array>

#include "Field.h"
#include "Colors.h"
#include "Position.h"

enum class RotationState
{
	UP, RIGHT, DOWN, LEFT,
};

using Figure = std::unordered_map<RotationState, std::vector<Position>>;

class Tet
{
public:
	Tet();
	void setPosition(sf::Vector2f pos);
	void draw(sf::RenderTarget& target);
	void move(size_t rows, size_t columns);
	std::vector<Position> getCellPositions();
protected:
	size_t calcWidth(const std::vector<Position>& positions);

	RotationState m_State;
	Figure m_Figure;
	unsigned int m_ColorIndex;

	size_t m_RowOffset;
	size_t m_ColumnOffset;

	sf::Vector2f m_OffsetWindow;

	Colors m_Colors;
};