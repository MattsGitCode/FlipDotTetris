#ifndef __GAME_H__
#define __GAME_H__

#include "Well.h"
#include "Tetrimino.h"

class Game;
typedef void (Game::*ButtonPressCallback)();
typedef bool (*ButtonPinStateFunction)();

class Game
{
	Well well;
	Tetrimino tetrimino;
	uint8_t level;
	uint32_t lastFallTime;
	
	uint8_t buttonStates;
	ButtonPinStateFunction buttonPinStateFunctions[3];
	ButtonPressCallback buttonCallbacks[3];
	

public:
	Game();
	~Game();
	
	void Draw(Buffer &buffer) const;
	void Tick(const uint32_t milliseconds);
protected:
private:
	Game( const Game &c );
	Game& operator=( const Game &c );
	
	void ProcessInputs();
	void RotatePressed();
	void MoveLeftPressed();
	void MoveRightPressed();
};

#endif //__GAME_H__
