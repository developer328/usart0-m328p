#ifndef _USART0_H
#define  _USART0_H

void usart_init(uint32_t baud, uint8_t speed);
void usart_sendChar(char acter);
void usart_sendStr(char *str);
char usart_getChar(void);
uint8_t usart_getStr(void);
void usart_clear(void);

#endif
