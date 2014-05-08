#include "Game.h"
#include "../Hardware/HardwareConfiguration.h"

const uint16_t LevelTetriminoFallRate[] = {
	500,
	800,
	700,
	600,
};

Game::Game()
	: well(), level(0), lastFallTime(0),
	buttonStates(0),
	buttonPinStateFunctions {
		&readLeftButtonPin, &readRightButtonPin,
		&readRotateButtonPin
	},
	buttonCallbacks {
		&Game::MoveLeftPressed, &Game::MoveRightPressed,
		&Game::RotatePressed
	}
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
	ProcessInputs();
	
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
	for (int i = 0; i < 3; ++i)
	{
		bool pinState = buttonPinStateFunctions[i]();
		bool buttonState = buttonStates & (1UL << i);
		if (pinState && !buttonState)
		{
			(*this.*(buttonCallbacks[i]))();
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
	tetrimino.MoveLeft();
}

void Game::MoveRightPressed()
{
	tetrimino.MoveRight();
}

void Game::RotatePressed()
{
	tetrimino.Rotate();
}
