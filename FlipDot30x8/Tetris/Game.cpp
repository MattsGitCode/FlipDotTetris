#include "Game.h"
#include "../Hardware/HardwareConfiguration.h"

const uint16_t LevelTetriminoFallRate[] = {
	500,
	300,
	150,
	80,
	40,
};

Game::Game()
{
}

Game::~Game()
{
}

void Game::Draw(Buffer &buffer) const
{
	well.Draw(buffer);
	tetrimino.Draw(buffer);
}

void Game::Tick(const uint32_t milliseconds)
{
	(*this.*(gameStateMap[state]))(milliseconds);
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
		state = GameState::ClearingRow;
	}
}

void Game::StateClearingRow(const uint32_t &milliseconds)
{
	if (milliseconds >= lastClearIncrementTime + 100)
	{
		lastClearIncrementTime = milliseconds;
		bool complete = well.IncrementRowClear(rowsToClear);
		
		if (complete)
		{
			state = GameState::Playing;
		}
	}
}
