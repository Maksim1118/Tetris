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
	void draw(sf::RenderTarget& target, bool isStatic = false);
	std::vector<Position> getCellPositions();
	void move(int rows, int columns);
	void rotate();
	void undoRotate();
	sf::Color getColor();
	sf::Vector2f getZeroPos();
	void setScale(float scale);
	void setPosition(sf::Vector2f pos);
	float getWidth();
	float getHeight();
protected:
	int calcWidth();
	int calcHeight();
	void normalizePos();
	RotationState getRandomRotationState();

	RotationState m_State;
	Figure m_Figure;
	unsigned int m_ColorIndex;

	sf::Vector2f m_Size;
	float m_Scale;

	int m_RowOffset;
	int m_ColumnOffset;

	float m_OffsetFromFieldX;
	float m_OffsetFromFieldY;

	sf::Vector2f m_Pos;

	Colors m_Colors;
};