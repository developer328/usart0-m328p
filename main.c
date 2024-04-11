#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart0.h"

char chr = '\0';

int main(void){
	usart_init(115200);
	DDRB |= (1<<5);

	while(1){
		chr = usart_getChar();

		if(chr != '\0'){
			usart_sendChar(chr);
			usart_sendChar(' ');	
			usart_sendStr(" Hello!! ");
		}

		_delay_ms(100);
	}
	return 0;
}
