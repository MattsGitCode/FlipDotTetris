#ifndef __ROTATION_H__
#define __ROTATION_H__

#include <avr/io.h>

class Buffer;
class Well;

class Rotation
{
	const uint8_t rows[4];
	
public:
	Rotation(const uint8_t &row1, const uint8_t &row2, const uint8_t &row3 = 0, const uint8_t &row4 = 0);
	Rotation( const Rotation &c );
	~Rotation();
	
	void Draw(const int8_t &destinationX, const int8_t &destinationY, Buffer &buffer) const;
	bool IsValid(const Well &well, const int8_t &x, const int8_t &y) const;
protected:
private:
	Rotation& operator=( const Rotation &c );

};

#endif //__ROTATION_H__
