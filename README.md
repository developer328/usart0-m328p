-ATmega328p USART0 8-bit Asynchronous, TX RX library
=======================================================================

#WARNING:
- If you optimize (OPTIMIZE == 1) that code, it uses 358bytes,
 but you can't write baud rate(9600, 115200, ETC) value because
 in this case baud rate to UBRRn, converter is disabled, it requiers 
 write UBRRn(103, 8, ETC) value(check in ATmega328p datasheet).

 Baud rate -> UBRRn (UX2n == 0):
 9600 -> 103
 38400 -> 25
 115200 -> 8

- Of this library target is small memory usage and fast execution.

- In code are preprocesors where user can active or deactive some modes:

1. Active or deactive RXCIEn ISR by change value of ISR_EN (Default value 
   is 1 as activated); 

2. user can change memory usage by changeing value of OPTIMIZE 
  (Default value is 0 as disabled);

3. User can active or deactive double speed mode by change value of XSPEED 
   (Default value is 1 as activated);


#Functions:

- void usart_init(uint32_t baud);
- void usart_sendChar(char acter);
- void usart_sendStr(char *str);
- char usart_getChar(void);
- char* usart_getStr(void);
- void usart_end(void);


#libraries

- #include <avr/io.h>
- #include <avr/interrupt.h>


#variables

- volatile char _RECEIVED_CHAR_ = '\0';


#ISR

- USART_RX_vect


#Configurations

- #define OPTIMIZE 0

- #define XSPEED 1

- #define ISR_EN 1


=========================================


#About developer

- youtube: https://www.youtube.com/channel/UCRLxLcBO9MSjiLtP3xOF5yw

- github: https://github.com/developer328

- twitter: https://twitter.com/nikoloz328


