/*
 * GccApplication1.c
 *
 * Created: 25.04.2020 13:15:06
 * Author : Jojo
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "usart.h"
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static char buffer[5];

int ADCRead()
{
	int ADCval;

	ADMUX = 0;         // use #0 ADC
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescaler for 16Mhz
	ADCSRA |= (1 << ADEN);   

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	while(ADCSRA & (1 << ADSC));      // wait for ADC to finish

	ADCval = ADCL;
	ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again

	return ADCval;
}


int main(void)
{
    usart_init();
	
    while (1)	{ 
		itoa(ADCRead(), buffer, 10);
		usart_send_string(buffer);
		_delay_ms(1000);
    }
}
