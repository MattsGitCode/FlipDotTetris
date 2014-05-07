#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include "Hardware/HardwareConfiguration.h"
#include "Hardware/Display.h"

#include "Tetris/Game.h"

volatile static uint32_t milliseconds;

ISR(TIMER1_COMPA_vect)
{
	++milliseconds;
}

int main(void)
{
	clock_prescale_set(clock_div_1);
	configurePorts();
	timer1EnableCtcMode(124);
	timer1EnableWithoutPrescaler();
	sei();
	
	
	Display display;
	display.Reset();
	
	Buffer buffer(true);

	Game game;
	

	while (1)
	{
		game.Tick(milliseconds);
		
		buffer.Clear();
		game.Draw(buffer);
		display.SetDisplay(buffer);
	}
}