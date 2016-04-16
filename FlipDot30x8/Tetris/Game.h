#ifndef __GAME_H__
#define __GAME_H__

#include "Well.h"
#include "Tetrimino.h"
#include "../Hardware/HardwareConfiguration.h"

class Game;
typedef void (Game::*ButtonPressCallback)();
typedef bool (*ButtonPinStateFunction)();
typedef void (Game::*GameStateCallback)(const uint32_t &milliseconds);

class Game
{
	enum GameState : uint8_t
	{
		Playing,
		ClearingRow,
		Gravity,
		NextLevel,
	};
	GameStateCallback gameStateMap[4] = {
		&Game::StatePlaying,
		&Game::StateClearingRow,
		&Game::StateGravity,
		&Game::StateNextLevel,
	};
	GameState state;

	// StatePlaying	
	Well well;
	Tetrimino tetrimino;
	uint8_t level = 0;
	uint32_t lastFallTime = 0;
	uint8_t score = 0;
	
	uint8_t buttonStates = 0;
	struct
	{
		ButtonPinStateFunction pinFunc;
		ButtonPressCallback callbackFunc;
	} buttonMap[3] = {
		{ &readLeftButtonPin, &Game::MoveLeftPressed },
		{ &readRightButtonPin, &Game::MoveRightPressed },
		{ &readRotateButtonPin, &Game::RotatePressed },
	};
	
	
	// StateClearingRow
	uint32_t rowsToClear;
	uint32_t lastClearIncrementTime = 0;
	
	// StateGravity
	uint32_t lastGravityIncrementTime = 0;

public:
	Game();
	~Game();
	
	void Draw(Buffer &buffer) const;
	void Tick(const uint32_t milliseconds);
protected:
private:
	Game( const Game &c );
	Game& operator=( const Game &c );
	
	void StatePlaying(const uint32_t &millseconds);
	void ProcessInputs();
	void RotatePressed();
	void MoveLeftPressed();
	void MoveRightPressed();
	void ProcessFall(const uint32_t milliseconds);
	void ProcessRowClears();
	
	void StateClearingRow(const uint32_t &milliseconds);
	void StateGravity(const uint32_t &milliseconds);
	void StateNextLevel(const uint32_t &milliseconds);
};

#endif //__GAME_H__
