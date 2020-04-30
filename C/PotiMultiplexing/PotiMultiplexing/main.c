#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart.h"


uint8_t indexPoti = 0;
char buffer[5];
int value;
/*
// static volatile int ADCval;
// 
// int ADCsingleREAD()
// {
// 	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
// 
// 	while(ADCSRA & (1 << ADSC));      // line waits for the ADC to finish
// 
// 	ADCval = ADCL;
// 	ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again
// 
// 	return ADCval;
// }
*/

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
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();    
	
	while (1)	{
		;
	}
}

ISR(ADC_vect)
{
	if (!indexPoti)	{
		value = ADCH;
		itoa(value, buffer, 10);
		buffer[4] = '\0';
		usart_send_string("Poti 1: ");	
		usart_send_string(buffer);
		ADMUX |= 1;
		indexPoti = 1;
	}
	else
	{
		value = ADCH;
		itoa(value, buffer, 10);
		buffer[4] = '\0';
		usart_send_string("Poti 2: ");
		usart_send_string(buffer);
		ADMUX &= ~1;
		indexPoti = 0;
	}		
}
