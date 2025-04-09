#include "Game.h"
#include <stdexcept>

using namespace sf;
using namespace std;

Game::Game()
	:m_IsTetDrop(false), m_ElapsedTime(0.f), m_DropInterval(DROP_INTERVAL), m_CurrTetIndex(0), m_GameOver(false)
{
	m_Tets = { LTet(), JTet(), ITet(), OTet(), STet(), TTet(), ZTet() };
	shuffleTets();

	if (m_Tets.size() == 0)
	{
		throw runtime_error("fail initialize vector Tets");
	}
	m_CurrTet = m_Tets.at(m_CurrTetIndex);
	m_NextTet = m_Tets.at(m_CurrTetIndex+1);
}

void Game::shuffleTets()
{
	for (size_t i = m_Tets.size() - 1; i > 0; --i)
	{
		size_t j = rand() % (i + 1);
		swap(m_Tets[i], m_Tets[j]);
	}
}

void Game::moveTetLeft()
{
	m_CurrTet.move(-1, 0);
	if (isTetOutside())
	{
		m_CurrTet.move(1, 0);
	}
	/*if (!m_GameOver)
	{
		m_CurrTet.move(-1, 0);
		if (isTetOutside())
		{
			m_CurrTet.move(1, 0);
		}
	}*/
}

void Game::moveTetRight()
{
	m_CurrTet.move(1, 0);
	if (isTetOutside())
	{
		m_CurrTet.move(-1, 0);
	}
	/*if (!m_GameOver)
	{
		m_CurrTet.move(1, 0);
		if (isTetOutside())
		{
			m_CurrTet.move(-1, 0);
		}
	}*/
}

void Game::moveTetDown()
{
	m_CurrTet.move(0, 1);
	if (isTetOutside() || !isTetFitsEmptyCell())
	{
		m_CurrTet.move(0, -1);
		lockTet();
	}
	/*if (!m_GameOver)
	{
		m_CurrTet.move(0, 1);
		if (isTetOutside() || !isTetFitsEmptyCell())
		{
			m_CurrTet.move(0, -1);
			lockTet();
		}
	}*/
}

bool Game::isTetOutside()
{
	vector<Position> tiles = m_CurrTet.getCellPositions();
	for (const auto& tile : tiles)
	{
		if (m_Field.isCollision(tile.m_Rows, tile.m_Columns))
			return true;		
	}
	return false;
}

bool Game::isTetFitsEmptyCell()
{
	vector<Position> tiles = m_CurrTet.getCellPositions();
	for (const auto& tile : tiles)
	{
		if (tile.m_Columns < 0) continue;
		if (!m_Field.isCellEmpty(tile.m_Rows, tile.m_Columns))
			return false;
	}
	return true;
}

bool Game::isUpLimit()
{
	vector<Position> tiles = m_CurrTet.getCellPositions();
	for (const auto& tile : tiles)
	{
		if (tile.m_Columns <= 0)
			return true;
	}
	return false;
}

void Game::rotateTet()
{
	if (!m_GameOver)
	{
		m_CurrTet.rotate();
		if (isTetOutside())
		{
			m_CurrTet.undoRotate();
		}
	}
}

void Game::lockTet()
{
	m_IsTetDrop = false;
	vector<Position> tiles = m_CurrTet.getCellPositions();
	for (const auto& tile : tiles)
	{
		if (tile.m_Columns < 0)
			continue;
		m_Field.getGrid()[tile.m_Rows][tile.m_Columns].setFillColor(m_CurrTet.getColor());
	}
	if (isUpLimit())
	{
		m_GameOver = true;
		return;
	}
	m_CurrTet = m_NextTet;
	m_Field.clearFullRows();
	++m_CurrTetIndex;
	if (m_CurrTetIndex == m_Tets.size())
	{
		m_CurrTetIndex = 0;
		shuffleTets();
	}
	m_NextTet = m_Tets[m_CurrTetIndex];
}

void Game::reset()
{
	m_Field.resetColorGrid();
	shuffleTets();
	m_CurrTetIndex = 0;
	m_CurrTet = m_Tets[m_CurrTetIndex];
	m_NextTet = m_Tets[m_CurrTetIndex + 1];
}

void Game::handleEvent(Event& event)
{
		
	if (event.type == Event::KeyPressed && !m_GameOver)
	{
		switch (event.key.code)
		{
			case Keyboard::Left:
			{
				moveTetLeft();
				break;
			}

			case Keyboard::Right:
			{
				moveTetRight();
				break;
			}

			case Keyboard::Down:
			{
				m_IsTetDrop = true;
				break;
			}
			case Keyboard::Up:
			{
				rotateTet();
				break;
			}
		}
	}
	if (event.type == Event::KeyPressed && m_GameOver)
	{
		if (event.key.code == Keyboard::Enter)
		{
			if (m_GameOver)
			{
				m_GameOver = false;
				reset();
			}
		}
	}
}

void Game::timeElapsed(float diff)
{
	if (m_GameOver) return;
	m_ElapsedTime += diff;

	float currentDropInterval = m_IsTetDrop ? DROP_INTERVAL_MIN : m_DropInterval;
	if (m_ElapsedTime >= currentDropInterval)
	{
		moveTetDown();
		m_ElapsedTime = 0.f;
		if (currentDropInterval > DROP_INTERVAL_MIN)
		{
			m_DropInterval -= 0.002f;
			if (m_DropInterval < DROP_INTERVAL_MIN)
				m_DropInterval = DROP_INTERVAL_MIN;
		}
	}
}

void Game::draw(RenderTarget& target)
{
	m_Field.draw(target);
	m_CurrTet.draw(target);
}


