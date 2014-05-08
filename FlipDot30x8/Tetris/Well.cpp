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
	for (int i = 0; i < 15; ++i)
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
