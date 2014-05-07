#include "../Hardware/Buffer.h"
#include "Rotation.h"
#include "Well.h"

Rotation::Rotation(const uint8_t &row1, const uint8_t &row2, const uint8_t &row3, const uint8_t &row4)
	: rows{ row1, row2, row3, row4 }
{
	
}

Rotation::~Rotation()
{
}

void Rotation::Draw(const int8_t &destinationX, const int8_t &destinationY, Buffer &buffer) const
{
	for (int8_t x = 0; x < 4 && (x + destinationX) < 8; ++x)
	for (int8_t y = 0; y < 4 && (y + destinationY) < 30; ++y)
	{
		if (rows[y] & (1UL << (3 - x)))
		{
			buffer.SetDot(x + destinationX, y + destinationY, true);
		}
	}
}

bool Rotation::IsValid(const Well &well, const int8_t &testX, const int8_t &testY) const
{
	for (int8_t y = 3; y >= 0; --y)
	{
		if (rows[y] == 0)
		{
			continue;
		}
		
		bool belowBottom = (testY + y) > 29;
		if (belowBottom)
		{
			return false;
		}
		
		for (int8_t x = 0; x < 4; ++x)
		{
			bool isPartOfShape = rows[y] & (1UL << (3 - x));
			if (isPartOfShape)
			{
				bool isBeyondLeft = (testX + x) < 0;
				bool isBeyondRight = (testX + x) > 7;
				if (isBeyondLeft || isBeyondRight)
				{
					return false;
				}
				
				bool isBlocked = well.IsBlocked(testX + x, testY + y);
				if (isBlocked)
				{
					return false;
				}
			}
		}
	}
	
	return true;
}
