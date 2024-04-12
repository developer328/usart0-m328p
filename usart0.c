/*
 * 8-APR-2024
 *
 * Library for ATmega328p 8-bit USART0 Asynchronous TX RX mode.
 *
 * If you optimize(OPTIMIZE == 1) that code, it uses 358bytes,
 * but you can't write baud rate(9600, 115200, ETC) value because
 * in this case baud rate to UBRRn converter is disabled, you need 
 * to write UBRRn(103, 8, ETC) value(check in ATmega328p datasheet).
 * 
 * Baud rate -> UBRRn:
 * 9600 -> 103
 * 38400 -> 25
 * 115200 -> 8
 *
 * youtube: https://www.youtube.com/channel/UCRLxLcBO9MSjiLtP3xOF5yw
 *
 * github: https://github.com/developer328
 *
 * twitter: https://twitter.com/nikoloz328
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart0.h"

#ifndef F_CPU 
#define F_CPU 16000000UL
#endif

/********************_CONFIGURATIONS_*************************/

#define OPTIMIZE 0

#define XSPEED 1

#define ISR_EN 1

/*************************************************************/

volatile char _RECEIVED_CHAR_ = '\0';

/*******************************************************************************/

void usart_init(uint32_t baud){
	cli();
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;

#if XSPEED == 1
	UCSR0A |= (1<<U2X0);	
#define MULTIPLY 8		
#elif XSPEED == 0
#define MULTIPLY 16
#endif

#if ISR_EN == 1
	UCSR0B |= (1<<RXCIE0);
#endif

	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	UCSR0C |= (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
	
#if OPTIMIZE == 0
	UBRR0 = (F_CPU/(baud*MULTIPLY)-1.0);	
#elif OPTIMIZE == 1
	UBRR0 = baud;
#endif
	sei();
}

/***************************************************************************/

void usart_sendChar(char acter){
	while(!(UCSR0A & (1<<UDRE0)))
	;

	UDR0 = acter;
}

/****************************************************************************/

void usart_sendStr(char *str){
	while(*str != 0x00){
		usart_sendChar(*str);
		str++;
	}
}

/****************************************************************************/

#if ISR_EN == 1
ISR(USART_RX_vect){
	_RECEIVED_CHAR_ = UDR0;
}
#endif

/***************************************************************************/

char usart_getChar(void){
#if ISR_EN == 0
	while(!(UCSR0A & (1<<RXC0)))
	;

	return UDR0;
#elif ISR_EN == 1
	char tmp = _RECEIVED_CHAR_;

	_RECEIVED_CHAR_ = '\0';

	return tmp;
#endif	
}

/******************************************************************************/

void clear_buffer(void){
	UDR0 = 0;
}

/************************************************************************/

void usart_end(void){
	cli();
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	UBRR0 = 0;
	UDR0 = 0;
	sei();
}

