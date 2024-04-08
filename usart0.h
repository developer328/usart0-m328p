#ifndef _USART0_H
#define  _USART0_H

void usart_init(float baud);
void usart_sendChar(char acter);
void usart_sendStr(char str[]);
char usart_getChar(void);
void usart_end(void);

#endif
