#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Buffer.h"


class Display
{
	struct DisplayOutputData
	{
		uint32_t data0;
		uint32_t data1;
		uint16_t data2;
		DisplayOutputData():data0(0), data1(0), data2(0) {};
	};
	
	Buffer frontBuffer;
	
public:
	Display();
	~Display();
	
	void Reset();
	void SetDot(const uint8_t &x, const uint8_t &y, const bool &on);
	void SetDisplay(const Buffer &buffer);
protected:
private:
	Display( const Display &c );
	Display& operator=( const Display &c );
	
	template<typename T> void shiftBytes(const T &bytes);
	void output(const DisplayOutputData &data);
	void setData(DisplayOutputData &data, const uint8_t &row, const uint8_t &column, const bool &on);
};

#endif //__DISPLAY_H__
