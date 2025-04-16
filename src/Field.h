#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <array>
#include <vector>

#include "Colors.h"

constexpr int ROWS = 12;
constexpr int COLUMNS = 24;

const sf::Vector2f startPos = sf::Vector2f(520.f, 60.f);

using Grid = std::array<std::array<sf::RectangleShape, COLUMNS>, ROWS>;

enum class FieldClearState
{
	searchFullRow,
	animation,
	clear,
	moveDown
};

class Field
{
public:
	Field();
	void draw(sf::RenderTarget & target);
	void setPosition(sf::Vector2f pos);
	bool isCollision(int row, int column);
	bool isCellEmpty(int row, int column);
	Grid & getGrid();
	void clearFullRows(float diff);
	void setState(FieldClearState state);
	FieldClearState getState() const;
	bool isAllRowsCleared() const;
	int getNumRowsCompleted() const;
	void reset();
	void update();
private:
	void resetColorGrid();
	void drawClearAnimation(sf::RenderTarget & target);
	void clearRowsAnimation(float diff);
	bool isRowFull();
	void clearRow();
	void moveRowDown();

	void forEachGridCell(std::function<void(size_t, size_t)> func);
	sf::RectangleShape m_Frame;

	Grid m_Grid;
	Colors m_Colors;

	FieldClearState m_ClearState;
	float m_ElapsedAnimationTime;

	std::vector<int> m_RowsAnimationAndClear;
	bool m_IsAnimationEnd;
	int m_CurrRow;
	int m_ClearRowsOffset;
};

extern int cellSize;