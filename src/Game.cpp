#include "Game.h"
#include <stdexcept>

#include "ResourceManager.h"
#include "Variables.h"

using namespace sf;
using namespace std;

Game::Game()
	:m_IsTetDrop(false), m_ElapsedTime(0.f), 
	m_DropInterval(DROP_INTERVAL), m_CurrTetIndex(0), m_GameOver(false), m_Score(0)
{
	m_Tets = { LTet(), JTet(), ITet(), OTet(), STet(), TTet(), ZTet() };
	shuffleTets();

	if (m_Tets.size() == 0)
	{
		throw runtime_error("fail initialize vector Tets");
	}
	m_CurrTet = m_Tets.at(m_CurrTetIndex);
	m_NextTet = m_Tets.at(m_CurrTetIndex+1);
	nextTetDataUpdate();
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
	if (isTetOutside() || !isTetFitsEmptyCell())
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
	if (isTetOutside() || !isTetFitsEmptyCell())
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

int Game::getScore()
{
	return m_Score;
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

void Game::nextTetDataUpdate()
{
	m_NextTet.setScale(1.8f);
	Vector2f pos =
	{
		m_NextTet.getZeroPos().x + rectNextTetPos.x + (rectNextTetSize.x - m_NextTet.getWidth()) / 2.f,
		m_NextTet.getZeroPos().y + rectNextTetPos.y + (rectNextTetSize.y - m_NextTet.getHeight()) / 2.f
	};
	m_NextTet.setPosition(pos);
}

void Game::rotateTet()
{
	if (!m_GameOver)
	{
		m_CurrTet.rotate();
		if (isTetOutside() || !isTetFitsEmptyCell())
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
	int countRowsCleared = m_Field.clearFullRows();
	updateScore(countRowsCleared, 0);

	++m_CurrTetIndex;
	m_CurrTet = m_Tets[m_CurrTetIndex % m_Tets.size()];
	if (m_CurrTetIndex + 1 >= m_Tets.size())
	{
		shuffleTets();
		m_CurrTetIndex = 0;
	}
	m_NextTet = m_Tets[(m_CurrTetIndex + 1) % m_Tets.size()];
	nextTetDataUpdate();

}

void Game::reset()
{
	m_Field.resetColorGrid();
	shuffleTets();
	m_CurrTetIndex = 0;
	m_CurrTet = m_Tets[m_CurrTetIndex];
	m_NextTet = m_Tets[m_CurrTetIndex + 1];
	m_Score = 0;
}

void Game::updateScore(int countLinesCleared, int moveDownPoints)
{
	switch (countLinesCleared)
	{
		case 1:
		{
			m_Score += 25;
			break;
		}
		case 2:
		{
			m_Score += 50;
			break;
		}
		case 3:
		{
			m_Score += 100;
			break;
		}
		default:
			break;
	}
	m_Score += moveDownPoints;
}

void Game::drawGameOver(RenderTarget& target)
{
	Font font = ResourceManager::getInstance().getFont(FontName::GAMEOVER);
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(80);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition(200.f, 200.f);

	target.draw(gameOverText);
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
				updateScore(0, 1);
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
	m_NextTet.draw(target, true);
}


