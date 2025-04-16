#pragma once


#include "Field.h"
#include "Tets.h"
#include "ResourceManager.h"
#include "Variables.h"

constexpr float DROP_INTERVAL = 0.6f;
constexpr float DROP_INTERVAL_MIN = 0.03f;

enum class GameState
{
	Playing, 
	ClearingRow,
	UpdateElements,
	Pause,
	GameOver
};

class Game
{
public:
	Game();
	void draw(sf::RenderTarget& target);
	void handleEvent(sf::Event& event);
	void timeElapsed(float diff);
	void moveTetLeft();
	void moveTetRight();
	void moveTetDown();
	int getScore();
	void pause();
	void play();
	void restart();
	void soundOff();
	void soundOn();
	bool isGameOver();
private:
	bool isTetOutside();
	bool isTetFitsEmptyCell();

	bool isUpLimit();

	void ciclingMove(float diff);
	void updateIndex();

	void nextTetDataUpdate();

	void initAudio();
	void musicRestart();
	bool isPlayingMusic(sf::Music& music, float volumeDecrease);
	void musicsHandleEvent();
	void allMusicPause();

	void rotateTet();
	void lockTet();
	void updateScore(int countLinesCleared, int moveDownPoints);

	void shuffleTets();
	Field m_Field;
	std::vector<Tet> m_Tets;
	Tet m_CurrTet;
	Tet m_NextTet;
	unsigned int m_CurrTetIndex;

	GameState m_State;

	sf::Music* m_BackGroundMusic;
	sf::Music* m_DropTetMusic;
	sf::Music* m_MoveTetMusic;
	sf::Music* m_RotateTetMusic;
	sf::Music* m_ClearLineMusic;
	sf::Music* m_GameOverMusic;

	std::vector<sf::Music*> m_GameMusics;

	bool m_IsTetDrop;
	bool m_IsGameOver;

	bool m_TetIsLock;

	bool m_GamePause;
	bool m_SoundOff;

	int m_Score;

	float m_ElapsedTime;
	float m_DropInterval;
};