#include <avr/io.h>
#include <avr/interrupt.h>

void init(void){
	//clear PD2 and PD3 and turn up pull-up
	DDRD &= ~((1 << DDD2) | (1 << DDD3));
	PORTD |= ((1 << PORTD2) | (1 << PORTD3));
	
	// set PD4 output and sink it
	DDRD |= (1 << DDD4);
	PORTD &= ~(1 << PORTD4);
	
	//set INT0 and INT1 to trigger on falling edge
	EICRA |= ((1 << ISC01) | (1 << ISC11));
	
	//turn ON INT0 and INT1
	EIMSK |= ((1 << INT0) | (1 << INT1));
	
	// set timer 0 to ctc mode to play chamber tone A ~ 440Hz and start timer
	TCCR0A |= (1 << WGM01);
	OCR0A = 70;
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
		; 
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
