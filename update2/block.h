#pragma once

#include <vector>
#include <Windows.h>

enum class BLOCK_TYPE
{
	SQUARE_BLOCK = 0,
//	-------
//	|  |  |
//	-------
//	|  |  |
//	-------
	RECT_BLOCK,
//	-------------
//	|  |  |  |  |
//	-------------
	CONVEX_BLOCK,
//	   ----
//	   |  |
//	----------
//	|  |  |  |
//	----------
	TYPE4_BLOCK,
	TYPE5_BLOCK
};

enum class BLOCK_COLOR
{
	DARKBULE = 0,
	IVORY,
	RED,
	YELLOW,
	GREEN,
	GRAY
};

enum class DIRECTION
{
	DIRECTION_1 = 0,
	DIRECTION_2,
	DIRECTION_3,
	DIRECTION_4
};

enum class BLOCK_STATUS
{
	UNDEFINE = 0,
	NORMAL,
};

class Block
{
public:
	Block()
	{
		m_cordinations.clear();
		m_direction = DIRECTION::DIRECTION_1;
		m_blockStatus = BLOCK_STATUS::UNDEFINE;
	};
	~Block()
	{

	}
	std::vector<POINT>& getCordination();

	BLOCK_COLOR& getColor();

	void Reset(BLOCK_TYPE& type, BLOCK_COLOR& color);

	DIRECTION& getDirection();
	void setDirection(DIRECTION& direction);

	BLOCK_STATUS& getBlockStatus();
	void setBlockStatus(BLOCK_STATUS& status);

	BLOCK_TYPE& getType();
	void setType(BLOCK_TYPE& type);

	void Fall();

	void Left();

	void Right();

	void Rotate();
private:
	std::vector<POINT> m_cordinations;
	BLOCK_TYPE m_type;
	BLOCK_COLOR m_color;
	DIRECTION m_direction;
	BLOCK_STATUS m_blockStatus;
};
