#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t direction = 1;


static void inline init()   {
	DDRD |= (1 << DDD6);
	DDRD |= (1 << DDD6);    
	OCR0A = 0xFF;     // set PWM for 100% duty cycle
	TCCR0A |= (1 << COM0A1);     // set none-inverting mode
	TCCR0A |= (1 << WGM01) | (1 << WGM00);     // set fast PWM Mode
	TCCR0B |= (1 << CS01);     // set prescaler to 8 and starts PWM
	
}

static void loop()  {
	while(1)    {
		if (direction)
			if (OCR0A)	{
				OCR0A >>= 1;
				_delay_ms(1000);
			}
			else
			direction = 0;
		else {
			if (OCR0A==255)
			direction = 1;
			else {
				OCR0A <<= 1;
				OCR0A |= 1;
				_delay_ms(1000);
			}
		}
	}
}

int main(void)  {
	init();
	loop();
}
