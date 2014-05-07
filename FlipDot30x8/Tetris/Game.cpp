#include "Game.h"

const uint16_t LevelTetriminoFallRate[] = {
	500,
	800,
	700,
	600,
};

Game::Game()
	: well(), level(0), lastFallTime(0)
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