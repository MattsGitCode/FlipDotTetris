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
