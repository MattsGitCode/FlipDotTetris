#ifndef __GAME_H__
#define __GAME_H__

#include "Well.h"
#include "Tetrimino.h"

class Game
{
	Well well;
	Tetrimino tetrimino;
	uint8_t level;
	uint32_t lastFallTime;

public:
	Game();
	~Game();
	
	void Draw(Buffer &buffer) const;
	void Tick(const uint32_t milliseconds);
protected:
private:
	Game( const Game &c );
	Game& operator=( const Game &c );
};

#endif //__GAME_H__
