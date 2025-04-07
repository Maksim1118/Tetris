#include "Field.h"
using namespace sf;

size_t cellSize = 40;
const float Field::thickness = 5.f;

Field::Field()
{
	m_Frame.setSize(Vector2f((cellSize) * ROWS, (cellSize) * COLUMNS));
	m_Frame.setFillColor(Color(70, 70, 70));
	m_Frame.setOutlineThickness(thickness);
	m_Frame.setOutlineColor(Color(170, 220, 20));

	forEachGridCell([this](size_t x, size_t y)
		{
			m_Grid[x][y].setSize(Vector2f((float)cellSize * 0.95f, (float)cellSize * 0.95f));
			m_Grid[x][y].setFillColor(Color::Black);
		});
}

void Field::forEachGridCell(std::function<void(size_t, size_t)> func)
{
	for (size_t y = 0; y < COLUMNS; ++y)
	{
		for (size_t x = 0; x < ROWS; ++x)
		{
			func(x, y);
		}
	}
}

void Field::setPosition(Vector2f pos)
{
	m_Frame.setPosition(pos.x + thickness, pos.y + thickness);
	forEachGridCell([this](size_t x, size_t y)
		{
			m_Grid[x][y].setPosition(
				Vector2f
				(
					m_Frame.getPosition().x + x * cellSize + 1,
					m_Frame.getPosition().y + y * cellSize + 1
				)
			);
		});
}

void Field::draw(RenderTarget& target)
{
	target.draw(m_Frame);
	forEachGridCell([&target,this](size_t x, size_t y)
		{
			target.draw(m_Grid[x][y]);
		});
}