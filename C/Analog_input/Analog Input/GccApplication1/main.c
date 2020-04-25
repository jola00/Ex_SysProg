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



int ADCsingleREAD(uint8_t adctouse)
{
	int ADCval;

	ADMUX = adctouse;         // use #1 ADC
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale for 8Mhz
	ADCSRA |= (1 << ADEN);    // Enable the ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish


	ADCval = ADCL;
	ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again

	return ADCval;
}


int main(void)
{
    usart_init();
	char buffer[5];
	int value;
	
    while (1)	{	
		value = ADCsingleREAD(0);
		itoa(value, buffer, 10);
		buffer[4] = '\0';
		usart_send_string(buffer);
		_delay_ms(500);
    }
}

