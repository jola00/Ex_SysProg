
#define F_CPU 16000000UL
#include <avr/io.h>
#include "usart.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int ADCval;

int ADCRead()
{
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale for 8Mhz
	ADCSRA |= (1 << ADEN);    // Enable the ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	while(ADCSRA & (1 << ADSC));		// wait for finish reading ADC

	ADCval = ADCL;
	ADCval += (ADCH << 8);    // ADCH is read so ADC can be updated again

	return ADCval;
}


int main(void)
{
	char buffer[5];
	
    usart_init();
	
	// use ADC0 as input with 10 bit resolution and Avcc as reference
	ADMUX = 0;         
	ADMUX |= (1 << REFS0);   
	ADMUX &= ~(1 << ADLAR);
	
    while (1)	{	
		itoa(ADCRead(), buffer, 10);
		buffer[4] = '\0';
		usart_send_string(buffer);
		_delay_ms(500);
    }
}
