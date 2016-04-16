#include "Well.h"
#include "Tetrimino.h"


Well::Well()
	: rows(true), height(0)
{
}

Well::~Well()
{
}

void Well::Draw(Buffer &destination) const
{
	destination.Merge(rows);
}

void Well::Settle(const Tetrimino &tetrimino)
{
	tetrimino.Draw(rows);
	
	const uint8_t (&data)[30] = rows.GetData();
	for (int i = 29; i >= 0; --i)
	{
		if (data[i] != 0)
		{
			height = i + 1;
			return;
		}
	}
	
	height = 0;
}

uint32_t Well::GetRowsToClear()
{
	uint32_t rowsToClear = 0;
	const uint8_t (&data)[30] = rows.GetData();
	for (int i = 0; i < 30; ++i)
	{
		if (data[i] == 255UL)
		{
			rowsToClear |= (1UL << i);
		}
	}
	return rowsToClear;
}

bool Well::IncrementRowClear(const uint32_t &rowsToClear)
{
	bool moreToClear = false;
	uint8_t (&data)[30] = rows.GetData();
	for (int i = 0; i < 30; ++i)
	{
		if (rowsToClear & (1UL << i))
		{
			data[i] <<= 1UL;
			if (data[i] != 0)
			{
				moreToClear = true;
			}
		}
	}
	
	return !moreToClear;
}

bool Well::IncrementGravity()
{
	uint8_t (&data)[30] = rows.GetData();
	int gapToFill = 0;
	for (; gapToFill < height; ++gapToFill)
	{
		if (data[gapToFill] == 0)
		{
			break;
		}
	}
	
	if (gapToFill >= height)
	{
		return true;
	}
	
	for (; gapToFill <= height; ++gapToFill)
	{
		data[gapToFill] = data[gapToFill + 1];
	}
	
	--height;
	
	return false;
}

void Well::ClearAll()
{
	rows.Clear(false);
}
