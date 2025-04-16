#include "Field.h"
using namespace sf;
using namespace std;

int cellSize = 40;
const float animationDur = 3.f;

Field::Field()
	:m_ElapsedAnimationTime(0.f), m_ClearState(FieldClearState::searchFullRow),m_IsAnimationEnd(false), m_ClearRowsOffset(0), m_CurrRow(COLUMNS -1)
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

void Field::clearFullRows(float diff)
{
	switch (m_ClearState)
	{
		case FieldClearState::searchFullRow:
		{
			if (isRowFull())
			{
				m_RowsAnimationAndClear.emplace_back(m_CurrRow);
				--m_CurrRow;
			}
			else if (m_ClearRowsOffset > 0)
			{
				m_ClearState = FieldClearState::moveDown;
			}
			else if (!m_RowsAnimationAndClear.empty())
			{
				m_ClearState = FieldClearState::clear;
			}
			else
				--m_CurrRow;
			break;
		}
		case FieldClearState::animation:
		{
			clearRowsAnimation(diff);
			if (m_IsAnimationEnd)
			{
				m_IsAnimationEnd = false;
				m_ClearRowsOffset = m_RowsAnimationAndClear.size();
				m_RowsAnimationAndClear.clear();
				m_ClearState = FieldClearState::searchFullRow;
			}
			break;
		}
		case FieldClearState::clear:
		{
			clearRow();
			m_ClearState = FieldClearState::animation;
			break;
		}
		case FieldClearState::moveDown:
		{
			moveRowDown();
			--m_CurrRow;
			m_ClearState = FieldClearState::searchFullRow;
			break;
		}
	}
}

void Field::setState(FieldClearState state)
{
	m_ClearState = state;
}

FieldClearState Field::getState() const
{
	return m_ClearState;
}

bool Field::isAllRowsCleared() const
{
	return m_CurrRow <= 0;
}

int Field::getNumRowsCompleted() const
{
	return m_ClearRowsOffset;
}


void Field::reset()
{
	resetColorGrid();
	update();
}

void Field::update()
{
	m_CurrRow = COLUMNS - 1;
	m_ClearRowsOffset = 0;
	m_RowsAnimationAndClear.shrink_to_fit();
}

void Field::resetColorGrid()
{
	forEachGridCell([this](size_t x, size_t y)
		{
			m_Grid[x][y].setFillColor(black);
		});
}

void Field::drawClearAnimation(sf::RenderTarget& target)
{
	float currSize = cellSize * (1.0f - (m_ElapsedAnimationTime / animationDur));
	for (const auto& currRow : m_RowsAnimationAndClear)
	{
		for (size_t x = 0; x < ROWS; ++x)
		{
			RectangleShape rect;
			rect.setSize(Vector2f(currSize, currSize));
			rect.setPosition(m_Grid[x][currRow].getPosition().x + (cellSize - currSize)/2.f, m_Grid[x][currRow].getPosition().y + (cellSize - currSize) / 2.f);
			rect.setFillColor(white);
			target.draw(rect);
		}
	}
}

void Field::clearRowsAnimation(float diff)
{
	m_ElapsedAnimationTime += diff;
	if (m_ElapsedAnimationTime >= animationDur)
	{
		m_ElapsedAnimationTime = 0.f;
		m_IsAnimationEnd = true;
	}
}

bool Field::isRowFull()
{
	for (size_t x = 0; x < ROWS; ++x)
	{
		if (m_Grid[x][m_CurrRow].getFillColor() == black)
		{
			return false;
		}
	}
	return true;
}

void Field::clearRow()
{
	for (const auto& currRow : m_RowsAnimationAndClear)
	{
		for (size_t x = 0; x < ROWS; ++x)
		{
			m_Grid[x][currRow].setFillColor(black);
		}
	}
}

void Field::moveRowDown()
{
	for (size_t x = 0; x < ROWS; ++x)
	{
		m_Grid[x][m_CurrRow + m_ClearRowsOffset].setFillColor(m_Grid[x][m_CurrRow].getFillColor());
		m_Grid[x][m_CurrRow].setFillColor(black);
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
	if (m_ElapsedAnimationTime != 0)
	{
		drawClearAnimation(target);
	}
}