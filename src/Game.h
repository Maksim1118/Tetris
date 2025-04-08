#pragma once


#include "Field.h"
#include "Tets.h"

constexpr size_t DROP_SPEED = 3;
constexpr float DROP_INTERVAL = 0.6f;
constexpr float DROP_INTERVAL_MIN = 0.03f;

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
private:
	bool isTetOutside();
	void shuffleTets();
	Field m_Field;
	std::vector<Tet> m_Tets;
	Tet m_CurrTet;
	Tet m_NextTet;
	unsigned int m_CurrTetIndex;

	bool m_IsTetDrop;

	float m_ElapsedTime;
	float m_DropInterval;
};