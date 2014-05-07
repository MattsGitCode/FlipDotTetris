#ifndef __WELL_H__
#define __WELL_H__

#include "../Hardware/Buffer.h"
class Tetrimino;

class Well
{
	Buffer rows;
	uint8_t height;

//functions
public:
	Well();
	~Well();
	
	void Draw(Buffer &buffer) const;
	void Settle(const Tetrimino &tetrimino);
	bool IsBlocked(const int8_t &x, const int8_t &y) const
	{
		return rows.IsSet(x, y);
	}
protected:
private:
	Well( const Well &c );
	Well& operator=( const Well &c );

}; //Well

#endif //__WELL_H__
