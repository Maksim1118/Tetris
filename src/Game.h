#pragma once


#include "Field.h"
#include "Tets.h"

constexpr float DROP_INTERVAL = 0.6f;
constexpr float DROP_INTERVAL_MIN = 0.03f;

enum class GameState
{
	Playing, 
	ClearingRow,
	UpdateElements,
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
private:
	bool isTetOutside();
	bool isTetFitsEmptyCell();

	bool isUpLimit();

	void playing(float diff);
	void updateIndex();

	void nextTetDataUpdate();

	void rotateTet();
	void lockTet();
	void reset();
	void updateScore(int countLinesCleared, int moveDownPoints);
	void drawGameOver(sf::RenderTarget& target);

	void shuffleTets();
	Field m_Field;
	std::vector<Tet> m_Tets;
	Tet m_CurrTet;
	Tet m_NextTet;
	unsigned int m_CurrTetIndex;

	GameState m_State;

	bool m_IsTetDrop;
	bool m_IsGameOver;

	bool m_TetIsLock;

	int m_Score;

	float m_ElapsedTime;
	float m_DropInterval;
};