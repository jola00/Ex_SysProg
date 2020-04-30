#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart.h"
#define THRESHOLD  1

uint8_t indexPoti = 0;
char buffer[5];
static volatile int value0 = 0;
static volatile int value1 = 0;
static volatile int temp_val = 0;
static uint8_t changed = 1;

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
		if (changed)	{
			itoa(value0, buffer, 10);
			buffer[4] = '\0';
			usart_send_string("Poti 1: ");
			usart_send_string(buffer);
			itoa(value1, buffer, 10);
			buffer[4] = '\0';
			usart_send_string("Poti 2: ");
			usart_send_string(buffer);
			changed = 0;
		}
		
	}
}

ISR(ADC_vect)
{
	if (!indexPoti)	{
		temp_val = ADCH;
		if (abs(temp_val - value0) > THRESHOLD)	{
			//changed = 1;
			value0 = temp_val;
			itoa(value0, buffer, 10);
			buffer[4] = '\0';
			usart_send_string("Poti 1: ");
			usart_send_string(buffer);
		}
		ADMUX |= 1;
		indexPoti = 1;
	}
	else
	{
		temp_val = ADCH;
		if (abs(temp_val - value1) > THRESHOLD)	{
			//changed = 1;
			value1 = temp_val;
			itoa(value1, buffer, 10);
			buffer[4] = '\0';
			usart_send_string("Poti 2: ");
			usart_send_string(buffer);
			//changed = 0;
		}
		ADMUX &= ~1;
		indexPoti = 0;
	}		
}
