#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

static const uint8_t count =  1; // number of lights 
/* durch const wird der Compiler dazu angehalten, falls Optimierung erlaubt sind, 
den Wert in den Assembler-Code zu kopieren --> Variable im Code-Segment, falls sie 
in den Assemblercode kopiert wird*/
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
	DDRD = 0b00111100;	// use 4 pins of port d	//DDRD = 0b00111100;
	//	PORTD |= ((1 << PORTD0) | (1 << PORTD1));	// Anschalten der Pull-Up-Wiederstände 
    /*Port B und D werden benutzt, da Port C für analoge Ausgänge benutzt wird*/
}

static inline void setBit(uint8_t place) {
	if(place>9) return;	// return, damit Programm auch im Fehlerfall weiterläuft; keine Prüfung auf kleiner null, da Uint
	if (place < 6)		// wenn bit kleiner 6, dann Ansteuerung eines Pins auf Port B
		PORTB |= (1 << place);
	else	// wenn bit größer 6, dann Ansteuerung eines Pins auf Port D
		PORTD |= (1 << ((place%6)+2));	// Modulo 6, weil wir 6 Lampen auf Port B verwenden		// ((place%6)+2)
}

static inline void delBit(uint8_t place)	{
	if(place>9) return;	// return, damit Programm auch im Fehlerfall weiterläuft; keine Prüfung auf kleiner null, da Uint
	if (place < 6)		// wenn bit kleiner 6, dann Ansteuerung eines Pins auf Port B
		PORTB &= ~(1 << place);
	else	// wenn bit größer 6, dann Ansteuerung eines Pins auf Port D
		PORTD &= ~(1 << ((place%6)+2));	// Modulo 6, weil wir 6 Lampen auf Port B verwenden		// ((place%6)+2)
}


static inline void mainloop()
{
    // clear output
	PORTD &= 0b11110000;	//0b11000011;
	PORTB &= 0b11000000;
	if(mode)	{
		while(1)    {
        for(int i = 0; i < count; ++i){
            setBit(currentBit+i*direction);
			delBit(currentBit+(i-count)*direction);
        }

		currentBit+=direction;
		if(currentBit < -1 || currentBit > 9)
		direction *= -1;
		
	_delay_ms(50);
    }}
	else
	{
		while(1)    {
        for(int i = 0; i < count; ++i){
            setBit((currentBit+i)%10);
			if(count <= (currentBit+i))	// Überprüfung, damit das Argument keinen negativen Wert ergibt und somit wieder bei der oberen Grenze 255 angefangen werden würde
				delBit((currentBit+i-count)%10);
        }

		currentBit+=direction;
	_delay_ms(50);
    }}
}

int main(void)
{
    init();
	mainloop();
}
