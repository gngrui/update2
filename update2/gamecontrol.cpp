#include "gamecontrol.h"

void GameControl::UpdateGameStatus(float deltaTime, GameResource* g)
{
	if (g->getBlock().getBlockStatus() == BLOCK_STATUS::UNDEFINE)
	{
		ResetBlock(g);
		return;
	}
	else
	{
		m_deltaTime += deltaTime;
		if (m_deltaTime >= 0.6)
		{
			if (BlockCanFall(g))
			{
				g->getBlock().Fall();
			}
			else
			{
				UpdateCellMap(g);
				g->EraseCell();
				ResetBlock(g);
			}
			m_deltaTime = 0;
		}
	}
}

void GameControl::RespondKeyBoardMSG(WPARAM wParam, LPARAM lParam, GameResource* g)
{
	if (wParam == VK_LEFT)
	{
		if (BlockCanLeft(g))
			g->getBlock().Left();
	}
	else if (wParam == VK_RIGHT)
	{
		if (BlockCanRight(g))
			g->getBlock().Right();
	}
	else if (wParam == VK_DOWN)
	{
		if (BlockCanFall(g))
			g->getBlock().Fall();
	}
	else if (wParam == VK_UP)
	{
		if (BlockCanRotate(g))
			g->getBlock().Rotate();
	}
}

BOOL GameControl::BlockCanFall(GameResource* g) const
{
	bool res = true;
	std::vector<POINT> v = g->getBlock().getCordination();
	for (POINT p : v)
	{
		if (p.y == 24)
			res = false;
		if (g->getisExist(p.x, p.y + 1))
			res = false;
	}
	return res;
}

BOOL GameControl::BlockCanLeft(GameResource* g) const
{
	bool res = true;
	std::vector<POINT> v = g->getBlock().getCordination();
	for (POINT p : v)
	{
		if (p.x == 0)
		{
			res = false;
			break;
		}
		if (g->getisExist(p.x - 1, p.y))
			res = false;
	}
	return res;
}

BOOL GameControl::BlockCanRight(GameResource* g) const
{
	bool res = true;
	std::vector<POINT> v = g->getBlock().getCordination();
	for (POINT p : v)
	{
		if (p.x == 9)
		{
			res = false;
			break;
		}
		if (g->getisExist(p.x + 1, p.y))
			res = false;
	}
	return res;
}

BOOL GameControl::BlockCanRotate(GameResource* g) const
{
	bool res = true;
	Block block = g->getBlock();
	block.Rotate();
	std::vector<POINT> v = block.getCordination();
	for (POINT p : v)
	{
		if (p.x < 0 || p.x > 9)
		{
			res = false;
			break;
		}
		if (p.y < 0 || p.y > 24)
		{
			res = false;
			break;
		}
		if (g->getisExist(p.x, p.y))
			res = false;
	}
	return res;
}

void GameControl::ResetBlock(GameResource* g)
{
	BLOCK_TYPE type;
	BLOCK_COLOR color;
	UINT uType = m_selectBlockType(m_e);
	UINT uColor = m_selectBlockColor(m_e);

	if (uType == static_cast<unsigned int>(BLOCK_TYPE::CONVEX_BLOCK))
	{
		type = BLOCK_TYPE::CONVEX_BLOCK;
	}
	else if (uType == static_cast<unsigned int>(BLOCK_TYPE::SQUARE_BLOCK))
	{
		type = BLOCK_TYPE::SQUARE_BLOCK;
	}
	else if (uType == static_cast<unsigned int>(BLOCK_TYPE::RECT_BLOCK))
	{
		type = BLOCK_TYPE::RECT_BLOCK;
	}
	else if (uType == static_cast<unsigned int>(BLOCK_TYPE::TYPE4_BLOCK))
	{
		type = BLOCK_TYPE::TYPE4_BLOCK;
	}
	else if (uType == static_cast<unsigned int>(BLOCK_TYPE::TYPE5_BLOCK))
	{
		type = BLOCK_TYPE::TYPE5_BLOCK;
	}

	if (uColor == static_cast<unsigned int>(BLOCK_COLOR::DARKBULE))
	{
		color = BLOCK_COLOR::GRAY;
	}
	else if (uColor == static_cast<unsigned int>(BLOCK_COLOR::GREEN))
	{
		color = BLOCK_COLOR::GREEN;
	}
	else if (uColor == static_cast<unsigned int>(BLOCK_COLOR::IVORY))
	{
		color = BLOCK_COLOR::IVORY;
	}
	else if (uColor == static_cast<unsigned int>(BLOCK_COLOR::RED))
	{
		color = BLOCK_COLOR::RED;
	}
	else if (uColor == static_cast<unsigned int>(BLOCK_COLOR::YELLOW))
	{
		color = BLOCK_COLOR::YELLOW;
	}
	g->getBlock().Reset(type, color);
}

void GameControl::UpdateCellMap(GameResource* g)
{
	std::vector<POINT> v = g->getBlock().getCordination();
	for (POINT p : v)
	{
		g->setCellExist(p.x, p.y);
		g->setCellColor(p.x, p.y, g->getBlock().getColor());
	}
}
