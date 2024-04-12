CC = avr-gcc
OBJCPY = avr-objcopy
AVRDUDE = avrdude
SIZE = avr-size

PORT = usb
PROG = usbasp
MCU = atmega328p
F_CPU = 16000000UL

CFLAGS = -mmcu=$(MCU) -F_CPU=$(F_CPU) -Os

SRC = $(shell ls *.c)

OBJ = $(SRC:.c=.o)

ELF = $(SRC:.c=.elf)

main.hex: main.elf
	$(OBJCPY) -O ihex $< $@

main.elf: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $?

upload: main.hex
	$(AVRDUDE) -p $(MCU) -c $(PROG) -P $(PORT) -b 115200 -U flash:w:$<

size:
	$(SIZE) --mcu=$(MCU) --format=avr $(ELF)

.PHONY: clean
clean:
	rm *.elf
