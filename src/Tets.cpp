#include "Tets.h"

ITet::ITet()
{
	m_ColorIndex = 1;
	m_Figure[RotationState::LEFT] = { Position(0,2), Position(1, 2), Position(2,2), Position(3,2) };
	m_Figure[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,1), Position(3,1) };
	m_Figure[RotationState::UP] = { Position(2,0), Position(2, 1), Position(2,2), Position(2,3) };
	m_Figure[RotationState::DOWN] = { Position(1,0), Position(1,1), Position(1,2), Position(1,3) };
	m_State = getRandomRotationState();
	size_t width = calcWidth(m_Figure[m_State]);
	normalizePos(m_Figure[m_State]);
	move((ROWS - width) / 2, 0);
}

JTet::JTet()
{
	m_ColorIndex = 2;
	m_Figure[RotationState::LEFT] = { Position(0,0), Position(0, 1), Position(1,1), Position(2,1) };
	m_Figure[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,1), Position(2,2) };
	m_Figure[RotationState::UP] = { Position(1,0), Position(1, 1), Position(1,2), Position(0,2) };
	m_Figure[RotationState::DOWN] = { Position(1,2), Position(1,1), Position(1,0), Position(2,0) };
	m_State =  getRandomRotationState();
	size_t width = calcWidth(m_Figure[m_State]);
	normalizePos(m_Figure[m_State]);
	move((ROWS - width)/2, 0);
}

LTet::LTet()
{
	m_ColorIndex = 3;
	m_Figure[RotationState::LEFT] = { Position(0,2), Position(0, 1), Position(1,1), Position(2,1) };
	m_Figure[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,0), Position(2,1) };
	m_Figure[RotationState::UP] = { Position(1,0), Position(1, 1), Position(1,2), Position(2,2) };
	m_Figure[RotationState::DOWN] = { Position(0,0), Position(1,0), Position(1,1), Position(1,2) };
	m_State = getRandomRotationState();
	size_t width = calcWidth(m_Figure[m_State]);
	normalizePos(m_Figure[m_State]);
	move((ROWS - width) / 2, 0);
}

OTet::OTet()
{
	m_ColorIndex = 4;
	m_Figure[RotationState::UP] = { Position(0,0), Position(0, 1), Position(1,0), Position(1,1) };
	m_State = getRandomRotationState();
	size_t width = calcWidth(m_Figure[m_State]);
	normalizePos(m_Figure[m_State]);
	move((ROWS - width) / 2, 0);
}

STet::STet()
{
	m_ColorIndex = 5;
	m_Figure[RotationState::LEFT] = { Position(1,0), Position(1, 1), Position(2,1), Position(2,2) };
	m_Figure[RotationState::RIGHT] = { Position(0,0), Position(0,1), Position(1,1), Position(1,2) };
	m_Figure[RotationState::UP] = { Position(0,1), Position(1, 1), Position(1,0), Position(2,0) };
	m_Figure[RotationState::DOWN] = { Position(0,2), Position(1, 2), Position(1,1), Position(2,1) };
	m_State = getRandomRotationState();
	size_t width = calcWidth(m_Figure[m_State]);
	normalizePos(m_Figure[m_State]);
	move((ROWS - width) / 2, 0);
}

TTet::TTet()
{
	m_ColorIndex = 6;
	m_Figure[RotationState::LEFT] = { Position(0,1), Position(1, 0), Position(1,1), Position(1,2) };
	m_Figure[RotationState::RIGHT] = { Position(1,0), Position(1, 1), Position(2,1), Position(1,2) };
	m_Figure[RotationState::UP] = { Position(0,1), Position(1,1), Position(1,2), Position(2,1) };
	m_Figure[RotationState::DOWN] = { Position(0,1), Position(1, 0), Position(1,1), Position(2,1) };
	m_State = getRandomRotationState();
	size_t width = calcWidth(m_Figure[m_State]);
	normalizePos(m_Figure[m_State]);
	move((ROWS - width) / 2, 0);
}

ZTet::ZTet()
{
	m_ColorIndex = 7;
	m_Figure[RotationState::LEFT] = { Position(0,2), Position(0,1), Position(1,1), Position(1,0) };
	m_Figure[RotationState::RIGHT] = { Position(1,2), Position(1, 1), Position(2,1), Position(2,0) };
	m_Figure[RotationState::UP] = { Position(0,0), Position(1,0), Position(1,1), Position(2,1) };
	m_Figure[RotationState::DOWN] = { Position(0,1), Position(1, 1), Position(1,2), Position(2,2) };
	m_State = getRandomRotationState();
	size_t width = calcWidth(m_Figure[m_State]);
	normalizePos(m_Figure[m_State]);
	move((ROWS - width) / 2, 0);
}