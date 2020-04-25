/*
 * usart.h
 *
 * Created: 25.04.2020 10:59:58
 *  Author: Dennis Wolf
 */ 


#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
#include <stdint.h>

#define FOSC 16000000                       // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1

void usart_init(void);
void usart_send(const uint8_t to_send);
void usart_send_string(const char* to_send);
uint8_t usart_receive(void);

#endif /* USART_H_ */