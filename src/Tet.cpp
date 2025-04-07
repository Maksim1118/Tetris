#include "Tet.h"

using namespace sf;
using namespace std;

Tet::Tet()
	: m_RowOffset(0), m_ColumnOffset(0), m_OffsetWindow(0.f, 0.f)
{
	m_Colors = getColors();
	m_State = getRandomRotationState();
}

void Tet::setPosition(Vector2f pos)
{
	m_OffsetWindow.x = pos.x + thicknessFrame;
	m_OffsetWindow.y = pos.y + thicknessFrame;
}

void Tet::draw(RenderTarget& target)
{
	vector<Position> tiles = getCellPositions();
	for (auto tile : tiles)
	{
		RectangleShape cell;
		cell.setSize(Vector2f((float)cellSize * 0.95f, (float)cellSize * 0.95f));
		cell.setFillColor(Color::White/*m_Colors[m_ColorIndex]*/);
		cell.setPosition(m_OffsetWindow.x + tile.m_Rows * cellSize + 1, m_OffsetWindow.y + tile.m_Columns * cellSize + 1);
		target.draw(cell);
	}
}

RotationState Tet::getRandomRotationState()
{
	size_t randIndex = rand() % stateCount;
	return static_cast<RotationState>(randIndex);
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