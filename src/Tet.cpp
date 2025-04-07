#include "Tet.h"

using namespace sf;
using namespace std;

Tet::Tet()
	:m_State(RotationState::UP), m_RowOffset(0), m_ColumnOffset(0), m_OffsetWindow(0.f, 0.f)
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
		RectangleShape cell;
		cell.setSize(Vector2f((float)cellSize * 0.07f, (float)cellSize * 0.07f));
		cell.setFillColor(m_Colors[m_ColorIndex]);
		cell.setPosition(tile.m_Rows * cellSize + 1, tile.m_Columns * cellSize + 1);
		target.draw(cell);
	}
}

void Tet::move(size_t rows, size_t columns)
{
	m_RowOffset += rows;
	m_ColumnOffset += columns;
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

vector<Position> Tet::getCellPositions()
{
	vector<Position> movedTiles;
	for (const auto& tile : m_Figure[m_State])
	{
		movedTiles.emplace_back(tile.m_Rows + m_RowOffset, tile.m_Columns + m_ColumnOffset);
	}
	return movedTiles;
}