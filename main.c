#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "usart0.h"

char chr = '\0';
char str[20];
uint8_t index1 = 0;

int main(void){
	usart_init(115200, 1);// Baud, Speed
	sei();
	DDRB |= (1<<5);
	PORTB &= ~(1<<5);

	usart_sendChar('\r');
	usart_sendChar('\n');
	usart_sendStr("Hello!");
	usart_sendChar('\r');
	usart_sendChar('\n');	
	
	while(1){
	
//		if(usart_count() > 0){	
//			chr = usart_getStr();
			chr = usart_getChar();			

			if(chr != '\0'){
				str[index1++] = chr;	
				usart_sendChar(chr);
			}

			if(strcmp(str, "hello") == 0){
				index1 = 0;
				usart_sendChar('\r');
				usart_sendChar('\n');		
				usart_sendStr("Welcome!!!");
				usart_sendChar('\r');
				usart_sendChar('\n');
				PORTB |= (1<<5);
			}
//		}

		_delay_ms(100);
	}
	return 0;
}
