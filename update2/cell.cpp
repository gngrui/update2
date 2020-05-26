#include "cell.h"

BOOL Cell::getisExist()
{
    return m_isExist;
}

void Cell::setisExist(BOOL v)
{
    m_isExist = v;
}

BLOCK_COLOR& Cell::getCellColor()
{
    return m_Color;
}

void Cell::setCellColor(BLOCK_COLOR& color)
{
    m_Color = color;
}

D2D1_RECT_F& Cell::getCellRect()
{
    return m_rect;
}

void Cell::setCellRect(D2D1_RECT_F& rect)
{
    m_rect = rect;
}
