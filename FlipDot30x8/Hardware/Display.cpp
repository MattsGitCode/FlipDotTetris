
#include "Display.h"
#include "HardwareConfiguration.h"


Display::Display()
{
	// Taking the pin high disables the output
	displayOutputEnablePinHigh();
}


Display::~Display()
{
}

void Display::Reset()
{
	Buffer buffer;
	buffer.Clear(true);
	SetDisplay(buffer);
	buffer.Clear();
	SetDisplay(buffer);
}

void Display::SetDot(const uint8_t &x, const uint8_t &y, const bool &on)
{
	DisplayOutputData data;
	setData(data, y, x, on);
	output(data);
	displayOutputEnablePinLow();
	_delay_us(1000);
	displayOutputEnablePinHigh();
}

void Display::SetDisplay(const Buffer &buffer)
{
	for (uint8_t x = 0; x < 30; ++x)
	for (uint8_t y = 0; y < 8; ++y)
	{
		bool oldSet = frontBuffer.columns[x] & (1UL <<  y);
		bool newSet = buffer.columns[x] & (1UL <<  y);
		if (oldSet != newSet)
		{
			SetDot(x, y, newSet);
			frontBuffer.SetDot(x, y, newSet);
		}
	}
}

void Display::setData(DisplayOutputData &data, const uint8_t &row, const uint8_t &column, const bool &on)
{
	data.data0 = 0;
	data.data1 = 0;
	data.data2 = 0;
	
	bool columnPositiveToTurnOff = (row ^ column) & 1UL;
	bool rowPositive;
	if (columnPositiveToTurnOff)
	{
		rowPositive = on;
	}
	else
	{
		rowPositive = !on;
	}
	
	uint8_t pins[2];
	
	if (rowPositive)
	{
		pins[0] = rowVcc[row];
		pins[1] = colGnd[column];
	}
	else
	{
		pins[0] = rowGnd[row];
		pins[1] = colVcc[column];
	}

	for (uint8_t i = 0; i < 2; ++i)
	{
		uint8_t pin = pins[i];
		if (pin < 32UL)
		{
			data.data0 |= 1UL << pin;
		}
		else if (pin < 64UL)
		{
			data.data1 |= 1UL << (pin - 32UL);
		}
		else
		{
			data.data2 |= 1UL << (pin - 64UL);
		}
	}
}

template<typename T>
void Display::shiftBytes(const T &bytes)
{
	uint8_t numberOfBits = sizeof(T) * 8;
	for (int8_t i = numberOfBits - 1; i >= 0; --i)
	{
		if (bytes & (1UL << i))
		{
			displayDataPinHigh();
			displayClockPinHigh();
			displayClockPinLow();
			displayDataPinLow();
		}
		else
		{
			displayClockPinHigh();
			displayClockPinLow();
		}
	}
}

void Display::output(const DisplayOutputData &data)
{
	displayLatchPinLow();
	
	shiftBytes(data.data2);
	shiftBytes(data.data1);
	shiftBytes(data.data0);
	
	displayLatchPinHigh();
}
