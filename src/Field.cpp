#include "Field.h"
using namespace sf;
using namespace std;

int cellSize = 40;

Field::Field()
{
	m_Colors = getTetColors();

	const float thicknessFrame = 5.f;
	m_Frame.setSize(Vector2f((cellSize) * ROWS, (cellSize) * COLUMNS));
	m_Frame.setFillColor(lightGray);
	m_Frame.setOutlineThickness(thicknessFrame);
	m_Frame.setOutlineColor(yellow_green);
	m_Frame.setPosition(startPos);

	forEachGridCell([this](size_t x, size_t y)
		{
			m_Grid[x][y].setSize(Vector2f((float)cellSize * 0.95f, (float)cellSize * 0.95f));
			m_Grid[x][y].setFillColor(black);
			m_Grid[x][y].setPosition(
				Vector2f
				(
					m_Frame.getPosition().x + x * cellSize + 1,
					m_Frame.getPosition().y + y * cellSize + 1
				)
			);
		});
}

void Field::resetColorGrid()
{
	forEachGridCell([this](size_t x, size_t y)
		{
			m_Grid[x][y].setFillColor(black);
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

bool Field::isCollision(int row, int column)
{
	return !(row >= 0 && row < ROWS && column < (int)COLUMNS);
}

bool Field::isCellEmpty(int row, int column)
{
	return m_Grid[row][column].getFillColor() == black;
}

Grid& Field::getGrid()
{
	return m_Grid;
}

int Field::clearFullRows()
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
	return completed;
}

bool Field::isRowFull(size_t column)
{
	for (size_t x = 0; x < ROWS; ++x)
	{
		cout << x << "  " << column << endl;
		if (m_Grid[x][column].getFillColor() == black)
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
		m_Grid[x][column].setFillColor(black);
	}
}

void Field::moveRowDown(size_t column, size_t numColumns)
{
	for (size_t x = 0; x < ROWS; ++x)
	{
		m_Grid[x][column + numColumns].setFillColor(m_Grid[x][column].getFillColor());
		m_Grid[x][column].setFillColor(black);
	}
}

void Field::setPosition(Vector2f pos)
{
	m_Frame.setPosition(pos);
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