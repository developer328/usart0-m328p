#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart0.h"


int main(void){
	usart_init(115200);

	while(1){
		//usart_sendChar('f');
		usart_sendStr("Hello!");
		_delay_ms(1000);
	}
	return 0;
}
