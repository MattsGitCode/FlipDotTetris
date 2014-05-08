#include <stdlib.h>
#include "Tetrimino.h"
#include "Rotation.h"

Rotation Rotations[7][4] = {
	{ // I
		Rotation(0, 0b1111, 0, 0),
		Rotation(0b0010, 0b0010, 0b0010, 0b0010),
		Rotation(0, 0, 0b1111, 0),
		Rotation(0b0100, 0b0100, 0b0100, 0b0100),
	},
	{ // J
		Rotation(0b100, 0b111, 0),
		Rotation(0b011, 0b010, 0b010),
		Rotation(0, 0b111, 0b001),
		Rotation(0b010, 0b010, 0b110),
	},
	{ // L
		Rotation(0b001, 0b111, 0),
		Rotation(0b010, 0b010, 0b011),
		Rotation(0, 0b111, 0b100),
		Rotation(0b110, 0b010, 0b010),
	},
	{ // O
		Rotation(0b11, 0b11),
		Rotation(0b11, 0b11),
		Rotation(0b11, 0b11),
		Rotation(0b11, 0b11),
	},
	{ // S
		Rotation(0b011, 0b110, 0),
		Rotation(0b010, 0b011, 0b001),
		Rotation(0, 0b011, 0b110),
		Rotation(0b100, 0b110, 0b010),
	},
	{ // T
		Rotation(0b010, 0b111, 0),
		Rotation(0b010, 0b011, 0b010),
		Rotation(0, 0b111, 0b010),
		Rotation(0b010, 0b110, 0b010),
	},
	{ // Z
		Rotation(0b110, 0b011, 0),
		Rotation(0b001, 0b011, 0b010),
		Rotation(0, 0b110, 0b011),
		Rotation(0b010, 0b110, 0b100),
	},
};

Tetrimino::Tetrimino()
{
	Randomise();
}


Tetrimino::~Tetrimino()
{
}

void Tetrimino::Draw(Buffer &buffer) const
{
	Rotations[(uint8_t)shape][rotationPhase].Draw(x, y, buffer);
}

void Tetrimino::Randomise()
{
	y = -4;
	x = 3;
	shape = (TetriminoShape)(rand() / (RAND_MAX / 8));
}

bool Tetrimino::CanFall(const Well &well) const
{
	return Rotations[(uint8_t)shape][rotationPhase].IsValid(well, x, y + 1);
}

bool Tetrimino::CanMoveLeft(const Well &well) const
{
	return Rotations[(uint8_t)shape][rotationPhase].IsValid(well, x - 1, y);
}

bool Tetrimino::CanMoveRight(const Well &well) const
{
	return Rotations[(uint8_t)shape][rotationPhase].IsValid(well, x + 1, y);
}

bool Tetrimino::CanRotate(const Well &well) const
{
	return Rotations[(uint8_t)shape][nextRotationPhase(rotationPhase)].IsValid(well, x, y);
}
