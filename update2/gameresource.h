#pragma once

#include "cell.h"

#define V_BLOCK 25
#define H_BLOCK 10

class GameResource
{
public:
	GameResource()
	{
		m_frame = D2D1::RectF(
			0,
			0,
			640,
			480
		);
		m_client = D2D1::RectF(
			0, 0,
			192,
			480
		);
		for (int y = 0; y < m_Vblock; y++)
		{
			for (int x = 0; x < m_Hblock; x++)
			{
				D2D1_RECT_F rect = D2D1::RectF(
					x * 19.2f,
					y * 19.2f,
					(x + 1) * 19.2f,
					(y + 1) * 19.2f
				);
				m_cellMap[y][x].setCellRect(rect);
			}
		}
	}
	~GameResource()
	{

	}
	
	BOOL getisExist(UINT x, UINT y);
	BLOCK_COLOR& getCellColor(UINT x, UINT y);
	D2D1_RECT_F& getCellRect(UINT x, UINT y);

	Block& getBlock();
	D2D1_RECT_F& getFrameRect();
	D2D1_RECT_F& getClientRect();

	void setCellExist(UINT x, UINT y);
	void setCellColor(UINT x, UINT y, BLOCK_COLOR& color);
	void EraseCell();

	const static UINT m_Vblock = V_BLOCK;
	const static UINT m_Hblock = H_BLOCK;
private:
	Cell m_cellMap[V_BLOCK][H_BLOCK];

	Block m_block;

	D2D1_RECT_F m_frame;
	D2D1_RECT_F m_client;
};