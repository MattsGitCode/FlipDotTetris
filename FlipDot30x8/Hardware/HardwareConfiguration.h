#include <avr/io.h>
#include <util/delay.h>

#ifndef HARDWARECONFIGURATION_H_
#define HARDWARECONFIGURATION_H_


#define PIN_FUNCS(NAME, PORT, PIN) \
inline void NAME##PinHigh() { PORT |= (1 << PIN); } \
inline void NAME##PinLow() { PORT &= ~(1 << PIN); } \
inline void NAME##Pin(const bool &state) { if (state) NAME##PinHigh(); else NAME##PinLow(); }


PIN_FUNCS(displayData, PORTD, PORTD2)
PIN_FUNCS(displayClock, PORTD, PORTD0)
PIN_FUNCS(displayLatch, PORTD, PORTD1)
PIN_FUNCS(displayOutputEnable, PORTD, PORTD3)

inline void configurePorts()
{
	DDRD |= 0b1111;
}

inline void timer1EnableCtcMode(const uint16_t &compareValue)
{
	TCCR1B |= (1 << WGM12);
	OCR1A = compareValue;
	TIMSK1 |= (1 << OCIE1A);
}

inline void timer1EnableWithoutPrescaler()
{
	TCCR1B |= (1 << CS11) | (1 << CS10);
	TCNT1 = 0;
}


#define rowGndStart 64
const uint8_t rowGnd[] = {
	rowGndStart + 6,
	rowGndStart + 4,
	rowGndStart + 1,
	rowGndStart + 0,
	rowGndStart + 3,
	rowGndStart + 2,
	rowGndStart + 5,
	rowGndStart + 7,
};

#define rowVccStart 72
const uint8_t rowVcc[] = {
	rowVccStart + 6,
	rowVccStart + 1,
	rowVccStart + 0,
	rowVccStart + 5,
	rowVccStart + 7,
	rowVccStart + 4,
	rowVccStart + 3,
	rowVccStart + 2,
};


#define blockA 0
#define blockB 16
#define blockC 32
#define blockD 48
#define col(name, offset)  const uint8_t name[30] = { \
	blockD + offset + 4, \
	blockD + offset + 1, \
	blockD + offset + 5, \
	blockD + offset + 2, \
	blockD + offset + 7, \
	blockD + offset + 0, \
	blockD + offset + 6, \
	blockD + offset + 3, \
	 \
	blockC + offset + 3, \
	blockC + offset + 5, \
	blockC + offset + 7, \
	blockC + offset + 2, \
	blockC + offset + 6, \
	blockC + offset + 0, \
	blockC + offset + 4, \
	blockC + offset + 1, \
	 \
	blockB + offset + 5, \
	blockB + offset + 3, \
	blockB + offset + 7, \
	blockB + offset + 4, \
	blockB + offset + 6, \
	blockB + offset + 2, \
	blockB + offset + 0, \
	blockB + offset + 1, \
	 \
	blockA + offset + 7, \
	blockA + offset + 4, \
	blockA + offset + 3, \
	blockA + offset + 2, \
	blockA + offset + 6, \
	blockA + offset + 5, \
}

col(colGnd, 0);
col(colVcc, 8);



#undef col
#undef blockA
#undef blockB
#undef blockC
#undef blockD
#undef rowGndStart
#undef rowVccStart


#endif /* HARDWARECONFIGURATION_H_ */