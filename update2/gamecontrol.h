#pragma once

#include "block.h"
#include "gameresource.h"

#include <Windows.h>
#include <random>
#include <ctime>

class GameControl
{
public:
	GameControl() : 
		m_e (static_cast<UINT>(std::time(nullptr))),
		m_selectBlockType
		(
			static_cast<unsigned int>(BLOCK_TYPE::SQUARE_BLOCK),
			static_cast<unsigned int>(BLOCK_TYPE::TYPE5_BLOCK)
		),
		m_selectBlockColor
		(
			static_cast<unsigned int>(BLOCK_COLOR::DARKBULE),
			static_cast<unsigned int>(BLOCK_COLOR::GREEN)
		)
	{

	}
	~GameControl()
	{

	}

	void UpdateGameStatus(float deltaTime, GameResource* g);

	void RespondKeyBoardMSG(WPARAM wParam, LPARAM lParam, GameResource* g);

private:
	BOOL BlockCanFall(GameResource* g) const;

	BOOL BlockCanLeft(GameResource* g) const;

	BOOL BlockCanRight(GameResource* g) const;

	BOOL BlockCanRotate(GameResource* g) const;

	void ResetBlock(GameResource* g);

	void UpdateCellMap(GameResource* g);

private:
	float m_deltaTime = 0;

	std::default_random_engine m_e;
	std::uniform_int_distribution<unsigned int> m_selectBlockType;
	std::uniform_int_distribution<unsigned int> m_selectBlockColor;
};