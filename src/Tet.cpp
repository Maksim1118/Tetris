#include "Tet.h"

using namespace sf;
using namespace std;

Tet::Tet()
	: m_RowOffset(0), m_ColumnOffset(0), m_OffsetFromFieldX(0), m_OffsetFromFieldY(0), m_Scale(1.f), m_Pos(startPos)
{
	m_Colors = getTetColors();
}

void Tet::draw(RenderTarget& target, bool isStatic)
{
	vector<Position> tiles = getCellPositions();
	for (auto tile : tiles)
	{
		if (!isStatic)
		{
			if (tile.m_Columns < 0)
				continue;
		}
		RectangleShape cell;
		cell.setSize(Vector2f((float)cellSize * m_Scale * 0.95f, (float)cellSize * m_Scale * 0.95f));
		cell.setFillColor(m_Colors[m_ColorIndex]);
		cell.setPosition(m_Pos.x + (float)tile.m_Rows * (float)cellSize * m_Scale + 1, m_Pos.y + (float)tile.m_Columns * (float)cellSize * m_Scale + 1);
		target.draw(cell);
	}
}

RotationState Tet::getRandomRotationState()
{
	size_t randIndex = rand() % m_Figure.size();
	return static_cast<RotationState>(randIndex);
}

void Tet::move(int rows, int columns)
{
	m_RowOffset += rows;
	m_ColumnOffset += columns;
}

void Tet::rotate()
{
	if (m_Figure.size() == 1) return;

	switch (m_State)
	{
	case RotationState::UP:
		m_State = RotationState::RIGHT;
		break;
	case RotationState::RIGHT:
		m_State = RotationState::DOWN;
		break;
	case RotationState::DOWN:
		m_State = RotationState::LEFT;
		break;
	case RotationState::LEFT:
		m_State = RotationState::UP;
		break;
	}
}

void Tet::undoRotate()
{
	if (m_Figure.size() == 1) return;

	switch (m_State)
	{
	case RotationState::UP:
		m_State = RotationState::LEFT;
		break;
	case RotationState::RIGHT:
		m_State = RotationState::UP;
		break;
	case RotationState::DOWN:
		m_State = RotationState::RIGHT;
		break;
	case RotationState::LEFT:
		m_State = RotationState::DOWN;
		break;
	}
}

Color Tet::getColor()
{
	return m_Colors[m_ColorIndex];
}

Vector2f Tet::getZeroPos()
{
	return { -m_OffsetFromFieldX * (float)cellSize * m_Scale, -m_OffsetFromFieldY * (float)cellSize * m_Scale};
}

void Tet::setScale(float scale)
{
	m_Scale = scale;
	m_Size *= m_Scale;
}

void Tet::setPosition(Vector2f pos)
{
	m_Pos = pos;
}

float Tet::getWidth()
{
	return m_Size.x;
}

float Tet::getHeight()
{
	return m_Size.y;
}

int Tet::calcWidth()
{
	vector<Position> positions = m_Figure[m_State];
	int minX = positions[0].m_Rows;
	int maxX = positions[0].m_Rows;
	for (const auto& pos : positions)
	{
		if (pos.m_Rows < minX) minX = pos.m_Rows;
		if (pos.m_Rows > maxX) maxX = pos.m_Rows;
	}
	return (maxX - minX) + 1;
}

int Tet::calcHeight()
{
	vector<Position> positions = m_Figure[m_State];
	int minY = positions[0].m_Columns;
	int maxY = positions[0].m_Columns;
	for (const auto& pos : positions)
	{
		if (pos.m_Columns < minY) minY = pos.m_Columns;
		if (pos.m_Columns > maxY) maxY = pos.m_Columns;
	}
	return (maxY - minY) + 1;
}

void Tet::normalizePos()
{
	vector<Position> positions = m_Figure[m_State];
	int minX = positions[0].m_Rows;
	int minY = positions[0].m_Columns;
	for (size_t i = 1; i < positions.size(); ++i)
	{
		if (positions[i].m_Rows < minX) minX = positions[i].m_Rows;
		if (positions[i].m_Columns < minY) minY = positions[i].m_Columns;
	}
	move(-minX, -minY);
}


vector<Position> Tet::getCellPositions()
{
	vector<Position> movedTiles;
	for (const auto& tile : m_Figure[m_State])
	{
		movedTiles.emplace_back(tile.m_Rows + m_RowOffset, tile.m_Columns + m_ColumnOffset);
	}
	return movedTiles;
}
