/*
 * usart.c
 *
 * Created: 25.04.2020 11:02:17
 *  Author: Dennis Wolf
 */ 
#include "usart.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

const char newLine[1] = {'\n'};

void usart_init(){
	/*Set baud rate */
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
                                 
}

void usart_send(const char *to_send){
	while ( !(UCSR0A & (1 << UDRE0)) ); //Wait until buffer is empty
	UDR0 = *to_send;
}

uint8_t usart_receive(){
		return UDR0;
}

void usart_send_string(const char *to_send){
	while(*to_send){
		usart_send(to_send++);
	}
	usart_send(newLine);
}

