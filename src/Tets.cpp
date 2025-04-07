#include "Tets.h"

ITet::ITet()
{
	m_ColorIndex = 0;
	cells[RotationState::LEFT] = { Position(0,2), Position(1, 2), Position(2,2), Position(3,2) };
	cells[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,1), Position(3,1) };
	cells[RotationState::UP] = { Position(2,0), Position(2, 1), Position(2,2), Position(2,3) };
	cells[RotationState::DOWN] = { Position(1,0), Position(1,1), Position(1,2), Position(1,3) };
	size_t width = calcWidth(cells[m_State]);
	move(ROWS / 2 - width, 0);
}

JTet::JTet()
{
	m_ColorIndex = 1;
	cells[RotationState::LEFT] = { Position(0,0), Position(0, 1), Position(1,1), Position(2,1) };
	cells[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,1), Position(2,2) };
	cells[RotationState::UP] = { Position(1,0), Position(1, 1), Position(1,2), Position(0,2) };
	cells[RotationState::DOWN] = { Position(1,2), Position(1,1), Position(1,0), Position(2,0) };
	size_t width = calcWidth(cells[m_State]);
	move(ROWS / 2 - width, 0);
}

LTet::LTet()
{
	m_ColorIndex = 2;
	cells[RotationState::LEFT] = { Position(0,2), Position(0, 1), Position(1,1), Position(2,1) };
	cells[RotationState::RIGHT] = { Position(0,1), Position(1, 1), Position(2,0), Position(2,1) };
	cells[RotationState::UP] = { Position(1,0), Position(1, 1), Position(1,2), Position(2,2) };
	cells[RotationState::DOWN] = { Position(0,0), Position(1,0), Position(1,1), Position(1,2) };
	size_t width = calcWidth(cells[m_State]);
	move(ROWS / 2 - width, 0);
}

OTet::OTet()
{
	m_ColorIndex = 3;
	m_Figure[RotationState::UP] = { Position(0,0), Position(0, 1), Position(1,0), Position(1,1) };
	size_t width = calcWidth(m_Figure[RotationState::UP]);
	move(ROWS / 2 - width, 0);
}

STet::STet()
{
	m_ColorIndex = 4;
	cells[RotationState::LEFT] = { Position(1,0), Position(1, 1), Position(2,1), Position(2,2) };
	cells[RotationState::RIGHT] = { Position(0,0), Position(0,1), Position(1,1), Position(1,2) };
	cells[RotationState::UP] = { Position(0,1), Position(1, 1), Position(1,0), Position(2,0) };
	cells[RotationState::DOWN] = { Position(0,2), Position(1, 2), Position(1,1), Position(2,1) };
	size_t width = calcWidth(cells[m_State]);
	move(ROWS / 2 - width, 0);
}

TTet::TTet()
{
	m_ColorIndex = 5;
	cells[RotationState::LEFT] = { Position(0,1), Position(1, 0), Position(1,1), Position(1,2) };
	cells[RotationState::RIGHT] = { Position(1,0), Position(1, 1), Position(2,1), Position(1,2) };
	cells[RotationState::UP] = { Position(0,1), Position(1,1), Position(1,2), Position(2,1) };
	cells[RotationState::DOWN] = { Position(0,1), Position(1, 0), Position(1,1), Position(2,1) };
	size_t width = calcWidth(cells[m_State]);
	move(ROWS / 2 - width, 0);
}

ZTet::ZTet()
{
	m_ColorIndex = 6;
	cells[RotationState::LEFT] = { Position(0,2), Position(0,1), Position(1,1), Position(1,0) };
	cells[RotationState::RIGHT] = { Position(1,2), Position(1, 1), Position(2,1), Position(2,0) };
	cells[RotationState::UP] = { Position(0,0), Position(1,0), Position(1,1), Position(1,2) };
	cells[RotationState::DOWN] = { Position(1,0), Position(1, 1), Position(1,2), Position(2,2) };
	size_t width = calcWidth(cells[m_State]);
	move(ROWS / 2 - width, 0);
}