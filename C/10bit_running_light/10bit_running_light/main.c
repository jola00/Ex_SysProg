#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

static const uint8_t count =  1; // number of lights 
/*
There are two modes availiable:
	-mode 0: light(s) turn on from left to right and start afterwards at the left side
	-mode 1: light(s) run from 0 to 9 and vice versa*/
static const uint8_t mode = 0;

static int8_t direction = 1;
static uint8_t currentBit = 0;

static inline void init()
{
	DDRB = 0b00111111;	// use 6 pins of port b
	DDRD = 0b00111100;	// use 4 pins of port d
}

static inline void setBit(uint8_t place) {
	if(place>9) return;	
	if (place < 6)	
		PORTB |= (1 << place);
	else	
		PORTD |= (1 << ((place%6)+2));	
}

static inline void delBit(uint8_t place)	{
	if(place>9) return;	
	if (place < 6)		
		PORTB &= ~(1 << place);
	else	
		PORTD &= ~(1 << ((place%6)+2));	
}

static inline void mainloop()
{
    // clear output
	PORTD &= 0b11110000;
	PORTB &= 0b11000000;
	if(mode)	 {
		while(1)    {
			for(int i = 0; i < count; ++i){
				setBit(currentBit+i*direction);
				delBit(currentBit+(i-count)*direction);
        }

		currentBit+=direction;
		if(currentBit < -1 || currentBit > 9)
			direction *= -1;
		_delay_ms(50);
		}
	}
	else  {
		while(1)    {
			for(int i = 0; i < count; ++i){
				setBit((currentBit+i)%10);
				if(count <= (currentBit+i))	
					delBit((currentBit+i-count)%10);
			}

			currentBit+=direction;
			_delay_ms(50);
		}
	}
}

int main(void) {
    init();
	mainloop();
}
