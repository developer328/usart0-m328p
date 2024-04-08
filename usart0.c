/*
 * 8-APR-2024
 *
 * Library for ATmega328p USART0 Asynchronous TX RX mode.
 *
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
#include <string.h>
#include <math.h>
#include "usart0.h"

void usart_init(float baud){
	cli();
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	//UCSR0A |= (1<<U2X0);
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	UCSR0C |= (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
	baud = (1000000.0/baud-1.0);	
	UBRR0 = ceil(baud);//converter doesn't works on 76800
	sei();
}

void usart_sendChar(char acter){
	while(!(UCSR0A & (1<<UDRE0)));

	if(acter <= 255)
		UDR0 = acter;
}

void usart_sendStr(char str[]){
	char len = strlen(str);
	
	for(uint16_t i = 0; i < len; i++){
		while(!(UCSR0A & (1<<UDRE0)));

		if(str[i] <= 255)
			UDR0 = str[i];
	}
}

char usart_getChar(void){
	while(!(UCSR0A & (1<<RXC0)));

	return UDR0;
}

void usart_end(void){
	cli();
	UCSR0A = 0;
	UCSR0B = 0;
	UCSR0C = 0;
	UBRR0 = 0;
	UDR0 = 0;
	sei();
}
