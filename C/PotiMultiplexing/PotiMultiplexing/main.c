#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "usart.h"

char buffer[5];

int main(void)
{
	usart_init();
	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts for ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();    
	
	while (1)	{
		;
	}
}

ISR(ADC_vect)
{
	if (ADMUX & 0b00000001)	
		usart_send_string("Poti 2: ");	
	else 
		usart_send_string("Poti 1: ");	

	itoa(ADCH, buffer, 10);
	buffer[4] = '\0';
	usart_send_string(buffer); // send input value
	ADMUX ^= 1;	// change ADC
}
