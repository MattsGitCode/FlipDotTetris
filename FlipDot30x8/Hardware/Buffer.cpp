#include <string.h>

#include "Buffer.h"
#include "Font.h"

Buffer::Buffer(const bool &rotate)
	: rotate(rotate)
{
	Clear();
}

Buffer::~Buffer()
{
}

void Buffer::Clear(const bool &on)
{
	memset(columns, on ? 0xFF : 0, sizeof(columns));
}

void Buffer::SetDot(const int8_t &x, const int8_t &y, const bool &on)
{
	int8_t dstX = x;
	int8_t dstY = y;
	TranslateCoordinates(dstX, dstY);
	
	if (dstX > 29 || dstY > 7)
	{
		return;
	}
	
	if (on)
	{
		columns[dstX] |= (1 << dstY);
	}
	else
	{
		columns[dstX] &= ~(1 << dstY);
	}
}

void Buffer::FillSquare(const int8_t &x1, const int8_t &y1, const int8_t &x2, const int8_t &y2)
{
	for (int8_t x = x1; x <= x2; ++x)
	for (int8_t y = y1; y <= y2; ++y)
	{
		SetDot(x, y);
	}
}

void Buffer::Text(const int8_t &x, const int8_t &y, const char &letter)
{
	int start = (letter - 32) * 3;
	for (int i = 0; i < 3; ++i)
	{
		columns[x + i] |= (font[start + i] << y);
	}
}

void Buffer::Text(const int8_t &x, const int8_t &y, const char *string)
{
	size_t len = strlen(string);
	for (uint8_t i = 0; i < len; ++i)
	{
		Text(x + (i*4), y, string[i]);
	}
}

void Buffer::Merge(const Buffer &from)
{
	for(uint8_t i = 0; i < 30; ++i)
	{
		columns[i] |= from.columns[i];
	}
}
