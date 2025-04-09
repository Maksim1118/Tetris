#include "Tet.h"

using namespace sf;
using namespace std;

Tet::Tet()
	: m_RowOffset(0), m_ColumnOffset(0), m_OffsetWindow(startPos)
{
	m_Colors = getColors();
}

void Tet::setPosition(Vector2f pos)
{
	m_OffsetWindow = pos;
}

void Tet::draw(RenderTarget& target)
{
	vector<Position> tiles = getCellPositions();
	for (auto tile : tiles)
	{
		if (tile.m_Columns < 0)
			continue;
		RectangleShape cell;
		cell.setSize(Vector2f((float)cellSize * 0.95f, (float)cellSize * 0.95f));
		cell.setFillColor(m_Colors[m_ColorIndex]);
		cell.setPosition(m_OffsetWindow.x + tile.m_Rows * cellSize + 1, m_OffsetWindow.y + tile.m_Columns * cellSize + 1);
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

size_t Tet::calcWidth(const vector<Position>& positions)
{
	size_t minX = positions[0].m_Rows;
	size_t maxX = positions[0].m_Rows;
	for (const auto& pos : positions)
	{
		if (pos.m_Rows < minX) minX = pos.m_Rows;
		if (pos.m_Rows > maxX) maxX = pos.m_Rows;
	}
	return (maxX - minX) + 1;
}

size_t Tet::calcHeight(const std::vector<Position>& positions)
{
	size_t minY = positions[0].m_Columns;
	size_t maxY = positions[0].m_Columns;
	for (const auto& pos : positions)
	{
		if (pos.m_Columns < minY) minY = pos.m_Columns;
		if (pos.m_Columns > maxY) maxY = pos.m_Columns;
	}
	return (maxY - minY) + 1;
}

void Tet::normalizePos(const vector<Position>& positions)
{
	size_t minX = positions[0].m_Rows;
	size_t minY = positions[0].m_Columns;
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
