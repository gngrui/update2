#include "block.h"

std::vector<POINT>& Block::getCordination()
{
	return m_cordinations;
}

BLOCK_COLOR& Block::getColor()
{
	return m_color;
}

void Block::Reset(BLOCK_TYPE& type, BLOCK_COLOR& color)
{
	m_cordinations.clear();
	m_blockStatus = BLOCK_STATUS::NORMAL;
	m_type = type;
	m_direction = DIRECTION::DIRECTION_1;

	if (type == BLOCK_TYPE::CONVEX_BLOCK)
	{
		POINT p;
		p.x = 4; p.y = 0; m_cordinations.push_back(p);
		p.x = 3; p.y = 1; m_cordinations.push_back(p);
		p.x = 4; p.y = 1; m_cordinations.push_back(p);
		p.x = 5; p.y = 1; m_cordinations.push_back(p);

	}
	else if (type == BLOCK_TYPE::RECT_BLOCK)
	{
		POINT p;
		p.x = 3; p.y = 0; m_cordinations.push_back(p);
		p.x = 4; p.y = 0; m_cordinations.push_back(p);
		p.x = 5; p.y = 0; m_cordinations.push_back(p);
		p.x = 6; p.y = 0; m_cordinations.push_back(p);
	}
	else if (type == BLOCK_TYPE::SQUARE_BLOCK)
	{
		POINT p;
		p.x = 4; p.y = 0; m_cordinations.push_back(p);
		p.x = 3; p.y = 0; m_cordinations.push_back(p);
		p.x = 4; p.y = 1; m_cordinations.push_back(p);
		p.x = 3; p.y = 1; m_cordinations.push_back(p);
	}
	else if (type == BLOCK_TYPE::TYPE4_BLOCK)
	{
		POINT p;
		p.x = 4; p.y = 1; m_cordinations.push_back(p);
		p.x = 5; p.y = 1; m_cordinations.push_back(p);
		p.x = 5; p.y = 0; m_cordinations.push_back(p);
		p.x = 6; p.y = 0; m_cordinations.push_back(p);
	}
	else if (type == BLOCK_TYPE::TYPE5_BLOCK)
	{
		POINT p;
		p.x = 3; p.y = 0; m_cordinations.push_back(p);
		p.x = 4; p.y = 0; m_cordinations.push_back(p);
		p.x = 5; p.y = 0; m_cordinations.push_back(p);
		p.x = 5; p.y = 1; m_cordinations.push_back(p);
	}

	if (color == BLOCK_COLOR::DARKBULE)
	{
		m_color = BLOCK_COLOR::DARKBULE;
	}
	else if (color == BLOCK_COLOR::GREEN)
	{
		m_color = BLOCK_COLOR::GREEN;
	}
	else if (color == BLOCK_COLOR::IVORY)
	{
		m_color = BLOCK_COLOR::IVORY;
	}
	else if (color == BLOCK_COLOR::RED)
	{
		m_color = BLOCK_COLOR::RED;
	}
	else if (color == BLOCK_COLOR::YELLOW)
	{
		m_color = BLOCK_COLOR::YELLOW;
	}
}

DIRECTION& Block::getDirection()
{
	return m_direction;
}

void Block::setDirection(DIRECTION& direction)
{
	m_direction = direction;
}

BLOCK_STATUS& Block::getBlockStatus()
{
	return m_blockStatus;
}

void Block::setBlockStatus(BLOCK_STATUS& status)
{
	m_blockStatus = status;
}

BLOCK_TYPE& Block::getType()
{
	return m_type;
}

void Block::setType(BLOCK_TYPE& type)
{
	m_type = type;
}

void Block::Fall()
{
	for (std::vector<POINT>::iterator it = m_cordinations.begin();
		it != m_cordinations.end();
		it++)
	{
		if (it->y < 24)
			it->y++;
	}
}

void Block::Left()
{
	for (std::vector<POINT>::iterator it = m_cordinations.begin();
		it != m_cordinations.end();
		it++)
	{
		if (it->x > 0)
			it->x--;
	}
}

void Block::Right()
{
	for (std::vector<POINT>::iterator it = m_cordinations.begin();
		it != m_cordinations.end();
		it++)
	{
		if (it->x < 9)
			it->x++;
	}
}

void Block::Rotate()
{
	if (m_type == BLOCK_TYPE::CONVEX_BLOCK)
	{
		if (m_direction == DIRECTION::DIRECTION_1)
		{
			POINT p;
			int y = 25;
			int x;
			for (POINT tp : m_cordinations)
			{
				if (tp.y < y)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y - 1; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_2;
		}
		else if (m_direction == DIRECTION::DIRECTION_2)
		{
			POINT p;
			int y;
			int x = 10;
			for (POINT tp : m_cordinations)
			{
				if (tp.x < x)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y - 1; m_cordinations.push_back(p);
			p.x = x; p.y = y - 1; m_cordinations.push_back(p);
			p.x = x - 1; p.y = y - 1; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_3;
		}
		else if (m_direction == DIRECTION::DIRECTION_3)
		{
			POINT p;
			int y = -1;
			int x;
			for (POINT tp : m_cordinations)
			{
				if (tp.y > y)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x - 1; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x - 1; p.y = y; m_cordinations.push_back(p);
			p.x = x - 1; p.y = y - 1; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_4;
		}
		else if (m_direction == DIRECTION::DIRECTION_4)
		{
			POINT p;
			int y;
			int x = -1;
			for (POINT tp : m_cordinations)
			{
				if (tp.x > x)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x - 1; p.y = y + 1; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_1;
		}
	}
	else if (m_type == BLOCK_TYPE::RECT_BLOCK)
	{
		if (m_direction == DIRECTION::DIRECTION_1)
		{
			POINT p;
			int y;
			int x = 10;
			for (POINT tp : m_cordinations)
			{
				if (tp.x < x)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x + 1; p.y = y; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y + 2; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y - 1; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_2;
		}
		else if (m_direction == DIRECTION::DIRECTION_2)
		{
			POINT p;
			int y;
			int x = 10;
			for (POINT tp : m_cordinations)
			{
				if (tp.x < x)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x + 2; p.y = y; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y; m_cordinations.push_back(p);
			p.x = x - 1; p.y = y; m_cordinations.push_back(p);
			p.x = x; p.y = y; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_1;
		}
	}
	else if (m_type == BLOCK_TYPE::SQUARE_BLOCK)
	{
	}
	else if (m_type == BLOCK_TYPE::TYPE4_BLOCK)
	{
		if (m_direction == DIRECTION::DIRECTION_1)
		{
			POINT p;
			int y;
			int x = 10;
			for (POINT tp : m_cordinations)
			{
				if (tp.x < x)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x + 1; p.y = y; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x; p.y = y - 1; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_2;
		}
		else if (m_direction == DIRECTION::DIRECTION_2)
		{
			POINT p;
			int y = 25;
			int x;
			for (POINT tp : m_cordinations)
			{
				if (tp.y < y)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x + 1; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y; m_cordinations.push_back(p);
			p.x = x + 2; p.y = y; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_1;
		}
	}
	else if (m_type == BLOCK_TYPE::TYPE5_BLOCK)
	{
		if (m_direction == DIRECTION::DIRECTION_1)
		{
			POINT p;
			int y = -1;
			int x = -1;
			for (POINT tp : m_cordinations)
			{
				if (tp.x > x && tp.y > y)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y; m_cordinations.push_back(p);
			p.x = x; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x; p.y = y + 2; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_2;
		}
		else if (m_direction == DIRECTION::DIRECTION_2)
		{
			POINT p;
			int y = 25;
			int x = 10;
			for (POINT tp : m_cordinations)
			{
				if (tp.x < x && tp.y < y)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x + 1; p.y = y; m_cordinations.push_back(p);
			p.x = x + 2; p.y = y; m_cordinations.push_back(p);
			p.x = x; p.y = y - 1; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_3;
		}
		else if (m_direction == DIRECTION::DIRECTION_3)
		{
			POINT p;
			int y = -1;
			int x = 10;
			for (POINT tp : m_cordinations)
			{
				if (tp.x < x && tp.y > y)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x; p.y = y - 2; m_cordinations.push_back(p);
			p.x = x; p.y = y - 1; m_cordinations.push_back(p);
			p.x = x - 1; p.y = y; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_4;
		}
		else if (m_direction == DIRECTION::DIRECTION_4)
		{
			POINT p;
			int y = -1;
			int x = -1;
			for (POINT tp : m_cordinations)
			{
				if (tp.x > x && tp.y > y)
				{
					y = tp.y;
					x = tp.x;
				}
			}
			m_cordinations.clear();
			p.x = x; p.y = y; m_cordinations.push_back(p);
			p.x = x; p.y = y + 1; m_cordinations.push_back(p);
			p.x = x - 1; p.y = y; m_cordinations.push_back(p);
			p.x = x - 2; p.y = y; m_cordinations.push_back(p);
			m_direction = DIRECTION::DIRECTION_1;
		}
	}
}
