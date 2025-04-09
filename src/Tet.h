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
	UP, RIGHT, DOWN, LEFT
};

using Figure = std::unordered_map<RotationState, std::vector<Position>>;

class Tet
{
public:
	Tet();
	void setPosition(sf::Vector2f pos);
	void draw(sf::RenderTarget& target);
	std::vector<Position> getCellPositions();
	void move(int rows, int columns);
	void rotate();
	void undoRotate();
	sf::Color getColor();
protected:
	size_t calcWidth(const std::vector<Position>& positions);
	size_t calcHeight(const std::vector<Position>& positions);
	void normalizePos(const std::vector<Position>& positions);
	RotationState getRandomRotationState();

	RotationState m_State;
	Figure m_Figure;
	unsigned int m_ColorIndex;

	int m_RowOffset;
	int m_ColumnOffset;

	sf::Vector2f m_OffsetWindow;

	Colors m_Colors;
};