#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <avr/io.h>

class Buffer
{
	friend class Display;
	
	uint8_t columns[30];
	bool rotate;
	
public:
	Buffer(const bool &rotate = false);
	~Buffer();
	
	void Clear(const bool &on = false);
	void SetDot(const int8_t &x, const int8_t &y, const bool &on = true);
	void FillSquare(const int8_t &x1, const int8_t &y1, const int8_t &x2, const int8_t &y2);
	void Text(const int8_t &x, const int8_t &y, const char &letter);
	void Text(const int8_t &x, const int8_t &y, const char *string);
	void Merge(const Buffer &from);
	
	inline bool IsSet(const int8_t &testX, const int8_t &testY) const
	{
		int8_t x = testX;
		int8_t y = testY;
		TranslateCoordinates(x, y);
		if (y > 7 || x > 29)
			return false;
		
		return columns[x] & (1UL << y);
	}
	
	inline uint8_t (&GetData())[30]
	{
		return columns;
	}
	
protected:
private:
	Buffer( const Buffer &c );
	Buffer& operator=( const Buffer &c );
	
	inline void TranslateCoordinates(int8_t &x, int8_t &y) const
	{
		if (rotate)
		{
			int8_t tmpX = x;
			x = 29 - y;
			y = tmpX;
		}
	}

}; //Buffer

#endif //__BUFFER_H__
