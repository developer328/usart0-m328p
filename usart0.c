/*
 * 8-APR-2024
 *
 * Library for ATmega328p 8-bit USART0 Asynchronous TX RX mode.
 *
 *  If you make optimization (OPTIMIZE == 1) of this code, it will uses
 * ~500bytes, but you will not be able to write baud rate(9600, 115200, 
 * ETC) value in 'usart_init();' because in this case baud rate to UBRRn 
 * converter is disabled, so you would write directly UBRRn(103, 8, ETC) 
 * value(check in ATmega328p datasheet).
 *
 * Baud rate -> UBRRn:
 * 9600 -> 103
 * 38400 -> 25
 * 115200 -> 8
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart0.h"

#ifndef F_CPU 
#define F_CPU 16000000UL
#endif

#define _BUFFER_SIZE 128

/****************_CONFIGURATIONS_*******************/

#define OPTIMIZE 0

#define ISR_EN 1

/****************************************************/

volatile static char _RECEIVED_CHAR_ = '\0';
volatile static char _RECEIVED_BUFFER_[_BUFFER_SIZE] = {0};
volatile static uint16_t _RX_COUNT0_ = 0;
volatile static uint8_t _TX_READY_ = 1;

/************************************************/

#if ISR_EN == 1

ISR(USART_RX_vect){
	volatile static uint8_t _BUFFER_INDEX_ = 0;
	_RECEIVED_CHAR_ = UDR0;
	_RECEIVED_BUFFER_[_BUFFER_INDEX_] = _RECEIVED_CHAR_;
	_BUFFER_INDEX_++;
	_RX_COUNT0_++;
	if(_BUFFER_INDEX_ >= _BUFFER_SIZE){
		_BUFFER_INDEX_ = 0;
	}
}

ISR(USART_TX_vect){
	_TX_READY_ = 1;
}

#endif

/****************************************************/

void usart_init(uint32_t baud, uint8_t speed){
	cli();
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;

	static uint8_t s = 16;
	
	if(speed == 1){
		UCSR0A |= (1<<U2X0);	
		s = 8;
	}
#if ISR_EN == 1
	UCSR0B |= (1<<RXCIE0) | (1<<TXCIE0);
#endif
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	UCSR0C |= (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);	

#if OPTIMIZE == 0
	UBRR0 = (F_CPU/(baud*s)-1.0);	
#elif OPTIMIZE == 1
	UBRR0 = baud;
#endif	
}

/**************************************************/

void usart_sendChar(char acter){
#if ISR_EN == 0
	while(!(UCSR0A & (1<<UDRE0)))
	;
#elif ISR_EN == 1
	while(_TX_READY_ == 0)
	;		
	_TX_READY_ = 0;
#endif
	UDR0 = acter;
}

/**************************************************/

void usart_sendStr(char *str){
	while(*str != 0x00){
		usart_sendChar(*str);
		str++;
	}
}

/************************************************/

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

/**********************************************************/
#if ISR_EN == 1
uint16_t usart_count(void){
	return _RX_COUNT0_;
}

/**********************************************************/

uint8_t usart_getStr(void){
	static uint8_t _BUFFER_INDEX_ = 0;
	uint8_t tmp = 0;
	tmp = _RECEIVED_BUFFER_[_BUFFER_INDEX_];
	_RECEIVED_BUFFER_[_BUFFER_INDEX_] = '\0';
	_BUFFER_INDEX_++;
	_RX_COUNT0_--;
	if(_BUFFER_INDEX_ >= _BUFFER_SIZE){
		_BUFFER_INDEX_ = 0;
	}
	return tmp;
}
#endif

/**********************************************************/

void clear_buffer(void){
	UDR0 = 0;
}

/***********************************************************/

void usart_clear(void){
	cli();
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	UBRR0 = 0;
	UDR0 = 0;
}

