#pragma once

#include "block.h"
#include <d2d1.h>

class Cell
{
public:
	Cell() = default;
	~Cell() {}

	BOOL getisExist();
	void setisExist(BOOL v);

	BLOCK_COLOR& getCellColor();
	void setCellColor(BLOCK_COLOR& color);

	D2D1_RECT_F& getCellRect();
	void setCellRect(D2D1_RECT_F& rect);

private:
	BLOCK_COLOR m_Color;
	D2D1_RECT_F m_rect;
	BOOL m_isExist = FALSE;
};