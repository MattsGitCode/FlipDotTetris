#include "Game.h"
#include "../Hardware/HardwareConfiguration.h"

const uint16_t LevelTetriminoFallRate[] = {
	300,
	200,
	150,
	80,
	55,
	10,
};

const uint8_t LevelScoreBoundaries[] = {
	5,
	10,
	15,
	20,
	25,
	255,
};

Game::Game()
{
}

Game::~Game()
{
}

static bool on = false;
static uint32_t lastOn = 0;
void Game::Draw(Buffer &buffer) const
{
	well.Draw(buffer);
	tetrimino.Draw(buffer);
	buffer.SetDot(0, 0, on);
}

void Game::Tick(const uint32_t milliseconds)
{
	(*this.*(gameStateMap[state]))(milliseconds);
	
	if (milliseconds > lastOn + 1000)
	{
		lastOn = milliseconds;
		on = !on;
	}
}

void Game::StatePlaying(const uint32_t &milliseconds)
{
	ProcessInputs();
	ProcessFall(milliseconds);
	ProcessRowClears();
}

void Game::ProcessFall(const uint32_t milliseconds)
{
	auto fallRate = LevelTetriminoFallRate[level];
	auto nextFallTime = lastFallTime + fallRate;
	if (milliseconds >= nextFallTime)
	{
		lastFallTime = milliseconds;
		
		if (tetrimino.CanFall(well))
		{
			tetrimino.Fall();
		}
		else
		{
			well.Settle(tetrimino);
			tetrimino.Randomise();
		}
	}
}

void Game::ProcessInputs()
{
	for (uint8_t i = 0; i < (sizeof(buttonMap) / sizeof(*buttonMap)); ++i)
	{
		bool pinState = buttonMap[i].pinFunc();
		bool buttonState = buttonStates & (1UL << i);
		if (pinState && !buttonState)
		{
			(*this.*(buttonMap[i].callbackFunc))();
			buttonStates |= (1UL << i);
		}
		else if (!pinState && buttonState)
		{
			buttonStates &= ~(1UL << i);
		}
	}
	
}

void Game::MoveLeftPressed()
{
	if (tetrimino.CanMoveLeft(well))
	{
		tetrimino.MoveLeft();
	}
}

void Game::MoveRightPressed()
{
	if (tetrimino.CanMoveRight(well))
	{
		tetrimino.MoveRight();
	}
}

void Game::RotatePressed()
{
	if (tetrimino.CanRotate(well))
	{
		tetrimino.Rotate();
	}
}

void Game::ProcessRowClears()
{
	rowsToClear = well.GetRowsToClear();
	if (rowsToClear != 0)
	{
		score += 1;
		state = GameState::ClearingRow;
	}
}

void Game::StateClearingRow(const uint32_t &milliseconds)
{
	if (milliseconds >= lastClearIncrementTime + 50)
	{
		lastClearIncrementTime = milliseconds;
		bool complete = well.IncrementRowClear(rowsToClear);
		
		if (complete)
		{
			if (LevelScoreBoundaries[level] < score)
			{
				state = GameState::NextLevel;
			}
			else
			{
				state = GameState::Gravity;
			}
		}
	}
}

void Game::StateGravity(const uint32_t &milliseconds)
{
	if (milliseconds > lastGravityIncrementTime + 50)
	{
		lastGravityIncrementTime = milliseconds;
		bool complete = well.IncrementGravity();
		
		if (complete)
		{
			state = GameState::Playing;
		}
	}
}

void Game::StateNextLevel(const uint32_t &milliseconds)
{
	level += 1;
	well.ClearAll();
	
	state = GameState::Playing;
}
