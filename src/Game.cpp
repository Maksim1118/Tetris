#include "Game.h"
#include <stdexcept>

using namespace sf;
using namespace std;

const float DROP_INTERVAL_DECREMENT = 0.001f;
const float DECREMENT_THRESHOLD = 5.f;
float DROP_INTERVAL = 0.6f;
float DROP_INTERVAL_MIN = 0.03f;

Game::Game()
	:m_IsTetDrop(false), m_ElapsedMoveTime(0.f), m_ElapsedTimeChangeInterval(0.f),
	m_DropInterval(DROP_INTERVAL), m_CurrTetIndex(0), m_IsGameOver(false), m_Score(0), 
	m_State(GameState::Playing), m_TetIsLock(false), m_GamePause(false), m_SoundOff(false)
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
	initAudio();
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
	else
	{
		if (!m_SoundOff)
			m_MoveTetMusic->play();
	}
}

void Game::moveTetRight()
{
	m_CurrTet.move(1, 0);
	if (isTetOutside() || !isTetFitsEmptyCell())
	{
		m_CurrTet.move(-1, 0);
	}
	else
	{
		if (!m_SoundOff)
			m_MoveTetMusic->play();
	}
}

void Game::moveTetDown()
{
	m_CurrTet.move(0, 1);
	if (isTetOutside() || !isTetFitsEmptyCell())
	{
		m_CurrTet.move(0, -1);
		m_TetIsLock = true;
	}
}

int Game::getScore() const
{
	return m_Score;
}

void Game::pause()
{
	m_GamePause = true;
}

void Game::play()
{
	m_GamePause = false;
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

void Game::ciclingMove(float diff)
{
	m_ElapsedMoveTime += diff;

	float currentDropInterval = m_IsTetDrop ? DROP_INTERVAL_MIN : m_DropInterval;
	if (m_ElapsedMoveTime >= currentDropInterval)
	{
		moveTetDown();
		m_ElapsedMoveTime = 0.f;
		if (!m_IsTetDrop)
		{
			m_ElapsedTimeChangeInterval += diff;
			if (m_ElapsedTimeChangeInterval > DECREMENT_THRESHOLD)
			{
				m_ElapsedTimeChangeInterval = 0.f;
				m_DropInterval -= DROP_INTERVAL_DECREMENT;
				if (m_DropInterval < DROP_INTERVAL_MIN)
					m_DropInterval = DROP_INTERVAL_MIN;
			}
		}
	}
}

void Game::updateIndex()
{
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
	m_CurrTet.rotate();
	if (isTetOutside() || !isTetFitsEmptyCell())
	{
		m_CurrTet.undoRotate();
	}
	else
	{  if(!m_SoundOff)
			m_RotateTetMusic->play();
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
}

void Game::restart()
{
	m_Field.reset();
	shuffleTets();
	m_CurrTetIndex = 0;
	m_CurrTet = m_Tets[m_CurrTetIndex];
	m_NextTet = m_Tets[m_CurrTetIndex + 1];
	nextTetDataUpdate();
	m_Score = 0;
	m_TetIsLock = false;
	m_IsTetDrop = false;
	m_IsGameOver = false;
	m_State = GameState::Playing;
	m_Field.setState(FieldClearState::searchFullRow);
	musicRestart();
}

void Game::soundOff()
{
	m_SoundOff = true;
	m_BackGroundMusic->stop();
}

void Game::soundOn()
{
	if(m_SoundOff)
		m_BackGroundMusic->play();
	m_SoundOff = false;
}

bool Game::isGameOver() const
{
	return m_IsGameOver;
}

void Game::initAudio()
{
	m_BackGroundMusic = &ResourceManager::getInstance().getSound(SoundName::BACK_GROUND);
	m_BackGroundMusic->setVolume(backGroundMusicVolume);
	m_BackGroundMusic->setLoop(true);
	m_BackGroundMusic->play();

	m_DropTetMusic = &ResourceManager::getInstance().getSound(SoundName::DROP);
	m_DropTetMusic->setVolume(DropTetMusicVolume);
	m_GameMusics.emplace_back(m_DropTetMusic);

	m_MoveTetMusic = &ResourceManager::getInstance().getSound(SoundName::MOVE);
	m_MoveTetMusic->setVolume(MoveTetMusicVolume);
	m_GameMusics.emplace_back(m_MoveTetMusic);

	m_RotateTetMusic = &ResourceManager::getInstance().getSound(SoundName::ROTATE);
	m_RotateTetMusic->setVolume(RotateTetMusicVolume);
	m_GameMusics.emplace_back(m_RotateTetMusic);

	m_ClearLineMusic = &ResourceManager::getInstance().getSound(SoundName::CLEARLINE);
	m_ClearLineMusic->setVolume(ClearLineMusicVolume);
	m_GameMusics.emplace_back(m_ClearLineMusic);

	m_GameOverMusic = &ResourceManager::getInstance().getSound(SoundName::GAMEOVER);
	m_GameOverMusic->setVolume(GameOverMusicVolume);
	m_GameMusics.emplace_back(m_GameOverMusic);
}

void Game::musicRestart()
{
	m_BackGroundMusic->stop();
	m_BackGroundMusic->setPlayingOffset(Time::Zero);
	m_BackGroundMusic->play();

	for (auto& music : m_GameMusics)
	{
		music->stop();
		music->setPlayingOffset(Time::Zero);
	}
}

bool Game::isPlayingMusic(Music& music, float volumeDecrease)
{
	if (music.getStatus() == Sound::Playing)
	{
		m_BackGroundMusic->setVolume(backGroundMusicVolume * volumeDecrease);
		return  true;
	}
	else if (music.getStatus() == Sound::Paused)
	{
		music.play();
	}
	return false;
}

void Game::musicsHandleEvent()
{
	bool isAnySoundPlaying = false;
	for (const auto& music : m_GameMusics)
	{
		if (isPlayingMusic(*music, 0.5f))
		{
			isAnySoundPlaying = true;
			break;
		}
	}
	
	if (!isAnySoundPlaying)
	{
		m_BackGroundMusic->setVolume(backGroundMusicVolume);
	}
}


void Game::allMusicPause()
{
	for (const auto& music : m_GameMusics)
	{
		music->pause();
	}
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


void Game::handleEvent(Event& event)
{
	musicsHandleEvent();
	if (event.type == Event::KeyPressed && m_State == GameState::Playing)
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
				if (!m_IsTetDrop && !m_SoundOff)
				{
					m_DropTetMusic->play();
				}
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
}

void Game::timeElapsed(float diff)
{

	switch (m_State)
	{
		case GameState::Playing:
		{
			if (m_GamePause)
			{
				m_State = GameState::Pause;
			}
			else if (m_TetIsLock)
			{
				lockTet();
				m_State = GameState::ClearingRow;
			}
			else
			{
				ciclingMove(diff);
			}
			break;
		}
		case GameState::ClearingRow:
		{
			if (isUpLimit())
			{
				m_State = GameState::GameOver;
				break;
			}
			m_Field.clearFullRows(diff);
			if (m_Field.getState() == FieldClearState::clear && !m_SoundOff)
			{
				m_ClearLineMusic->play();
			}
			if(m_Field.isAllRowsCleared())
				m_State = GameState::UpdateElements;
			break;
		}
		case GameState::Pause:
		{
			allMusicPause();
			if (!m_GamePause)
				m_State = GameState::Playing;
			break;
		}
		case GameState::UpdateElements:
		{
			m_Field.setState(FieldClearState::searchFullRow);
			updateScore(m_Field.getNumRowsCompleted(), 0);
			updateIndex();
			m_Field.update();
			m_TetIsLock = false;
			m_State = GameState::Playing;
			break;
		}
		case GameState::GameOver:
		{
			if (!m_IsGameOver && !m_SoundOff)
			{
				m_GameOverMusic->play();
			}
			m_IsGameOver = true;
			break;
		}
	}
}

void Game::draw(RenderTarget& target)
{
	m_Field.draw(target);
	if(!m_TetIsLock)
		m_CurrTet.draw(target); 
	m_NextTet.draw(target, true);
}


