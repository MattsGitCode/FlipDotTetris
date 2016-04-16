#ifndef __TETRIMINO_H__
#define __TETRIMINO_H__

#include <avr/io.h>

class Buffer;
class Rotation;
class Well;

enum class TetriminoShape : uint8_t { I, J, L, O, S, T, Z };

class Tetrimino
{
	TetriminoShape shape;
	uint8_t rotationPhase;
	int8_t x;
	int8_t y;
	
public:
	Tetrimino();
	~Tetrimino();
	Tetrimino( const Tetrimino &c );
	
	void Draw(Buffer &buffer) const;
	
	inline void Rotate()
	{
		rotationPhase = nextRotationPhase(rotationPhase);
	}
	
	inline void MoveLeft()
	{
		x -= 1;
	}
	
	inline void MoveRight()
	{
		x += 1;
	}
	
	inline void Fall()
	{
		y += 1;
	}
	
	void Randomise();
	bool CanFall(const Well &well) const;
	bool CanRotate(const Well &well) const;
	bool CanMoveLeft(const Well &well) const;
	bool CanMoveRight(const Well &well) const;
protected:
private:
	Tetrimino& operator=( const Tetrimino &c );

	inline static uint8_t nextRotationPhase(const uint8_t &after)
	{
		return after == 3 ? 0 : (after + 1);
	}
};

#endif //__TETRIMINO_H__
