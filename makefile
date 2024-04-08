CC = avr-gcc
OBJCPY = avr-objcopy
AVRDUDE = avrdude
SIZE = avr-size

PORT = usb
PROG = usbasp
MCU = atmega328p
F_CPU = 16000000UL

CFLAGS = -mmcu=$(MCU) -F_CPU=$(F_CPU) -Os

SRC = *.c

main.hex: main.elf
	$(OBJCPY) -O ihex $< $@

main.elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

upload: main.hex
	$(AVRDUDE) -p $(MCU) -c $(PROG) -P $(PORT) -b 115200 -U flash:w:$<

size:
	

.PHONY: clean
clean:
	rm *.elf
