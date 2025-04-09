#include "Field.h"
using namespace sf;
using namespace std;

size_t cellSize = 40;

Field::Field()
{
	m_Colors = getColors();

	m_Frame.setSize(Vector2f((cellSize) * ROWS, (cellSize) * COLUMNS));
	m_Frame.setFillColor(Color(200, 200, 200));
	m_Frame.setOutlineThickness(thicknessFrame);
	m_Frame.setOutlineColor(Color(170, 220, 20));

	forEachGridCell([this](size_t x, size_t y)
		{
			m_Grid[x][y].setSize(Vector2f((float)cellSize * 0.95f, (float)cellSize * 0.95f));
			m_Grid[x][y].setFillColor(m_Colors.at(0));
		});
}

void Field::forEachGridCell(function<void(size_t, size_t)> func)
{
	for (size_t y = 0; y < COLUMNS; ++y)
	{
		for (size_t x = 0; x < ROWS; ++x)
		{
			func(x, y);
		}
	}
}

bool Field::isCollision(size_t row, size_t column)
{
	return !(row >= 0 && row < ROWS && column >= 0 && column < COLUMNS);
}

bool Field::isCellEmpty(size_t row, size_t column)
{
	return m_Colors[0] == m_Grid[row][column].getFillColor();
}

Grid& Field::getGrid()
{
	return m_Grid;
}

void Field::clearFullRows()
{
	size_t completed = 0;
	for (int y = COLUMNS - 1; y >= 0; --y)
	{
		if (isRowFull(y))
		{
			clearRow(y);
			++completed;
		}
		else if (completed > 0)
		{
			moveRowDown(y, completed);
		}
	}
}

bool Field::isRowFull(size_t column)
{
	for (size_t x = 0; x < ROWS; ++x)
	{
		cout << x << "  " << column << endl;
		if (m_Grid[x][column].getFillColor() == m_Colors[0])
		{
			return false;
		}
	}
	return true;
}

void Field::clearRow(size_t column)
{
	for (size_t x = 0; x < ROWS; ++x)
	{
		m_Grid[x][column].setFillColor(m_Colors[0]);
	}
}

void Field::moveRowDown(size_t column, size_t numColumns)
{
	for (size_t x = 0; x < ROWS; ++x)
	{
		m_Grid[x][column + numColumns].setFillColor(m_Grid[x][column].getFillColor());
		m_Grid[x][column].setFillColor(m_Colors[0]);
	}
}

void Field::setPosition(Vector2f pos)
{
	m_Frame.setPosition(pos.x + thicknessFrame, pos.y + thicknessFrame);
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