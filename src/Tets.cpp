#include "Tets.h"

using namespace sf;

ITet::ITet()
{
	m_ColorIndex = 0;
	m_Figure[RotationState::LEFT] = { Position(0,2), Position(1, 2), Position(2,2), Position(3,2) };
	m_Figure[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,1), Position(3,1) };
	m_Figure[RotationState::UP] = { Position(2,0), Position(2, 1), Position(2,2), Position(2,3) };
	m_Figure[RotationState::DOWN] = { Position(1,0), Position(1,1), Position(1,2), Position(1,3) };
	m_State = getRandomRotationState();
	m_Size = Vector2f(calcWidth() * cellSize, calcHeight() * cellSize);
	m_OffsetFromFieldX = (ROWS - calcWidth()) / 2;
	m_OffsetFromFieldY = -calcHeight();
	normalizePos();
	move(m_OffsetFromFieldX, m_OffsetFromFieldY);
	
}

JTet::JTet()
{
	m_ColorIndex = 1;
	m_Figure[RotationState::LEFT] = { Position(0,0), Position(0, 1), Position(1,1), Position(2,1) };
	m_Figure[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,1), Position(2,2) };
	m_Figure[RotationState::UP] = { Position(1,0), Position(1, 1), Position(1,2), Position(0,2) };
	m_Figure[RotationState::DOWN] = { Position(1,2), Position(1,1), Position(1,0), Position(2,0) };
	m_State = getRandomRotationState();
	m_Size = Vector2f(calcWidth() * cellSize, calcHeight() * cellSize);
	m_OffsetFromFieldX = (ROWS - calcWidth()) / 2;
	m_OffsetFromFieldY = -calcHeight();
	normalizePos();
	move(m_OffsetFromFieldX, m_OffsetFromFieldY);
}

LTet::LTet()
{
	m_ColorIndex = 2;
	m_Figure[RotationState::LEFT] = { Position(0,2), Position(0, 1), Position(1,1), Position(2,1) };
	m_Figure[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,0), Position(2,1) };
	m_Figure[RotationState::UP] = { Position(1,0), Position(1, 1), Position(1,2), Position(2,2) };
	m_Figure[RotationState::DOWN] = { Position(0,0), Position(1,0), Position(1,1), Position(1,2) };
	m_State = getRandomRotationState();
	m_Size = Vector2f(calcWidth() * cellSize, calcHeight() * cellSize);
	m_OffsetFromFieldX = (ROWS - calcWidth()) / 2;
	m_OffsetFromFieldY = -calcHeight();
	normalizePos();
	move(m_OffsetFromFieldX, m_OffsetFromFieldY);
}

OTet::OTet()
{
	m_ColorIndex = 3;
	m_Figure[RotationState::UP] = { Position(0,0), Position(0, 1), Position(1,0), Position(1,1) };
	m_State = RotationState::UP;
	m_Size = Vector2f(calcWidth() * cellSize, calcHeight() * cellSize);
	m_OffsetFromFieldX = (ROWS - calcWidth()) / 2;
	m_OffsetFromFieldY = -calcHeight();
	normalizePos();
	move(m_OffsetFromFieldX, m_OffsetFromFieldY);
}

STet::STet()
{
	m_ColorIndex = 4;
	m_Figure[RotationState::LEFT] = { Position(1,0), Position(1, 1), Position(2,1), Position(2,2) };
	m_Figure[RotationState::RIGHT] = { Position(0,0), Position(0,1), Position(1,1), Position(1,2) };
	m_Figure[RotationState::UP] = { Position(0,1), Position(1, 1), Position(1,0), Position(2,0) };
	m_Figure[RotationState::DOWN] = { Position(0,2), Position(1, 2), Position(1,1), Position(2,1) };
	m_State = getRandomRotationState();
	m_Size = Vector2f(calcWidth() * cellSize, calcHeight() * cellSize);
	m_OffsetFromFieldX = (ROWS - calcWidth()) / 2;
	m_OffsetFromFieldY = -calcHeight();
	normalizePos();
	move(m_OffsetFromFieldX, m_OffsetFromFieldY);
}

TTet::TTet()
{
	m_ColorIndex = 5;
	m_Figure[RotationState::LEFT] = { Position(0,1), Position(1, 0), Position(1,1), Position(1,2) };
	m_Figure[RotationState::RIGHT] = { Position(1,0), Position(1, 1), Position(2,1), Position(1,2) };
	m_Figure[RotationState::UP] = { Position(0,1), Position(1,1), Position(1,2), Position(2,1) };
	m_Figure[RotationState::DOWN] = { Position(0,1), Position(1, 0), Position(1,1), Position(2,1) };
	m_State = getRandomRotationState();
	m_Size = Vector2f(calcWidth() * (float)cellSize * m_Scale, calcHeight() * (float)cellSize * m_Scale);
	m_OffsetFromFieldX = (ROWS - calcWidth()) / 2;
	m_OffsetFromFieldY = -calcHeight();
	normalizePos();
	move(m_OffsetFromFieldX, m_OffsetFromFieldY);
}

ZTet::ZTet()
{
	m_ColorIndex = 6;
	m_Figure[RotationState::LEFT] = { Position(0,2), Position(0,1), Position(1,1), Position(1,0) };
	m_Figure[RotationState::RIGHT] = { Position(1,2), Position(1, 1), Position(2,1), Position(2,0) };
	m_Figure[RotationState::UP] = { Position(0,0), Position(1,0), Position(1,1), Position(2,1) };
	m_Figure[RotationState::DOWN] = { Position(0,1), Position(1, 1), Position(1,2), Position(2,2) };
	m_State = getRandomRotationState();
	m_Size = Vector2f(calcWidth() * (float)cellSize * m_Scale, calcHeight() * (float)cellSize * m_Scale);
	m_OffsetFromFieldX = (ROWS - calcWidth()) / 2;
	m_OffsetFromFieldY = -calcHeight();
	normalizePos();
	move(m_OffsetFromFieldX, m_OffsetFromFieldY);
}