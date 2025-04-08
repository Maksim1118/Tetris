#include "Game.h"

using namespace sf;
using namespace std;

Game::Game()
	:m_IsTetDrop(false), m_ElapsedTime(0.f), m_DropInterval(DROP_INTERVAL), m_CurrTetIndex(0)
{
	m_Tets = { LTet(), JTet(), ITet(), OTet(), STet(), TTet(), ZTet() };
	shuffleTets();
	m_CurrTet = m_Tets.at(m_CurrTetIndex);
	/*m_NextTet = m_Tets.at(m_CurrTetIndex+1);*/

	m_Field.setPosition(Vector2f(0.f, 0.f));
	m_CurrTet.setPosition(Vector2f(0.f, 0.f));
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
}

void Game::moveTetRight()
{
	m_CurrTet.move(1, 0);
	if (isTetOutside())
	{
		m_CurrTet.move(-1, 0);
	}
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

void Game::moveTetDown()
{
	m_CurrTet.move(0, 1);
	if (isTetOutside())
	{
		m_CurrTet.move(0, -1);
	}
}

void Game::rotateTet()
{
	m_CurrTet.rotate();
	if (isTetOutside())
	{
		m_CurrTet.undoRotate();
	}
}

void Game::handleEvent(Event& event)
{
	if (event.type == Event::KeyPressed)
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
}

void Game::timeElapsed(float diff)
{
	m_ElapsedTime += diff;

	float currentDropInterval = m_IsTetDrop ? DROP_INTERVAL_MIN : m_DropInterval;
	if (m_ElapsedTime >= currentDropInterval)
	{
		moveTetDown();
		m_ElapsedTime = 0.f;
		if (currentDropInterval > DROP_INTERVAL_MIN)
		{
			m_DropInterval -= 0.02f;
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


