#include <avr/io.h>
#include <avr/interrupt.h>

void init(void){
	//clear PD2 and PD3
	DDRD &= ~((1 << DDD2) | (1 << DDD3));
	
	// set PD4 output
	DDRD |= (1 << DDD4);

	// sink PD4
	PORTD &= ~(1 << PORTD4);
	
	//turn ON the PullUP
	PORTD |= ((1 << PORTD2) | (1 << PORTD3));
	//PD2 and PD3 is now an input with pull-up enabled
	
	//set INT0 and INT1 to trigger on falling edge
	EICRA |= ((1 << ISC01) | (1 << ISC11));
	
	//turn ON INT0 and INT1
	EIMSK |= ((1 << INT0) | (1 << INT1));
	
	// set timer 0 to ctc mode
	TCCR0A |= (1 << WGM01);
	//set OCR0A to play chamber tone A ~ 440Hz
	OCR0A = 70;
	// set prescaler to 256 and start timer
	TCCR0B |= (1 << CS02);
	// enable interrupt for timer 0
	TIMSK0 |= (1 << OCIE0A);

	// enable general interrupts
	sei();

}

int main(void)
{
	init();
	while (1)
	{
		; // Semikolon symbolisiert, dass hier Interrupts von Interesse sind
	}
}

ISR(INT0_vect){
	// set ocr to play c1 ~ 261,626Hz
	OCR0A = 118;
}

ISR(INT1_vect){
	// set ocr to play chamber tone a
	OCR0A = 70;
}

ISR (TIMER0_COMPA_vect){
	PORTD ^= (1 << PORTD4);
}
