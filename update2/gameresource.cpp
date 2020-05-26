#include "gameresource.h"

BOOL GameResource::getisExist(UINT x, UINT y)
{
	return m_cellMap[y][x].getisExist();
}

BLOCK_COLOR& GameResource::getCellColor(UINT x, UINT y)
{
	return m_cellMap[y][x].getCellColor();
}

D2D1_RECT_F& GameResource::getCellRect(UINT x, UINT y)
{
	return m_cellMap[y][x].getCellRect();
}

Block& GameResource::getBlock()
{
	return m_block;
}

D2D1_RECT_F& GameResource::getFrameRect()
{
	return m_frame;
}

D2D1_RECT_F& GameResource::getClientRect()
{
	return m_client;
}

void GameResource::setCellExist(UINT x, UINT y)
{
	m_cellMap[y][x].setisExist(true);
}

void GameResource::setCellColor(UINT x, UINT y, BLOCK_COLOR& color)
{
	m_cellMap[y][x].setCellColor(color);
}

void GameResource::EraseCell()
{
	for (int y = 24; y >= 0; y--)
	{
		bool isFull = true;
		bool checkAgain = true;
		for (int x = 0; x < 10; x++)
		{
			if (!m_cellMap[y][x].getisExist())
				isFull = false;
		}
		if (isFull)
		{
			for (int i = 0; i < 10; i++)
				m_cellMap[y][i].setisExist(false);
			for (int j = y; j >= 1; j--)
			{
				for (int k = 0; k < 10; k++)
				{
					m_cellMap[j][k].setisExist(m_cellMap[j - 1][k].getisExist());
					m_cellMap[j][k].setCellColor(m_cellMap[j - 1][k].getCellColor());
				}
			}
		}
		for (int x = 0; x < 10; x++)
		{
			if (!m_cellMap[y][x].getisExist())
				checkAgain = false;
		}
		if (checkAgain)
			y++;
	}
}
