-ATmega328p USART0 8-bit Asynchronous, TX RX library
=======================================================================

#WARNING:

- If you make optimization (OPTIMIZE == 1) of this code, it will uses
 ~500bytes, but you will not be able to write baud rate(9600, 115200, 
 ETC) value in 'usart_init();' because in this case baud rate to UBRRn 
 converter is disabled, so you would write directly UBRRn(103, 8, ETC) 
 value(check in ATmega328p datasheet).

 Baud rate -> UBRRn (UX2n == 0):
 9600 -> 103
 38400 -> 25
 115200 -> 8


- Of this library target is small memory usage and fast execution.


- In code are preprocesors where user is able active or deactive some modes:

1. Active or deactive ISR by change value of ISR_EN (Default value 
   is 1 as activated); 

2. user can change memory usage by changeing value of OPTIMIZE 
  (Default value is 0 as disabled);


#Functions:

- void usart_init(uint32_t baud, uint8_t speed);
- void usart_sendChar(char acter);
- void usart_sendStr(char *str);
- char usart_getChar(void);
- uint8_t usart_getStr(void);
- void usart_clear(void);


#libraries

- #include <avr/io.h>
- #include <avr/interrupt.h>


#variables

- volatile static char _RECEIVED_CHAR_ = '\0';
- volatile static char _RECEIVED_BUFFER_[_BUFFER_SIZE] = {0};
- volatile static uint16_t _RX_COUNT0_ = 0;
- volatile static uint8_t _TX_READY_ = 1;


#ISR

- USART_RX_vect
- USART_TX_vect


#Configurations

- #define OPTIMIZE 0

- #define ISR_EN 1


#Hardware requirements

- ATmega328p


#Software requirements

- AVR-GCC
- AVR-OBJCOPY
- AVRDUDE
- AVR-SIZE
- MAKE


=========================================


#About developer

- youtube: https://www.youtube.com/channel/UCRLxLcBO9MSjiLtP3xOF5yw

- github: https://github.com/developer328

- twitter: https://twitter.com/hardwarelevel0


