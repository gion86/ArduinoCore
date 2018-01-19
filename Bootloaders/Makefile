# Makefile for ATmegaBOOT - Optiboot bootloaders
# E.Lins, 18.7.2005
# $Id$
#
# - removed unused platforms
# - changed programmer to usbasp
# - added target for 328P @8MHz and @1MHz
# Gionata Boccalini, 01.11.2017 

#
# Instructions
#
# To make bootloader .hex file:
# make atmega8
# make atmega168
# make atmega328
#
# To burn bootloader .hex file:
# make atmega8_isp
# make atmega168_isp
# make atmega328_isp

# program name should not be changed...
PROGRAM    = optiboot

# The default behavior is to build using tools that are in the users
# current path variables.

# Enter the parameters for the avrdude isp tool:

# USBasp configuration
#ISPTOOL	= usbasp
#ISPPORT	= usb
#ISPSPEED   = 

# Pololu configuration
ISPTOOL	   = stk500v2
ISPPORT	   = /dev/ttyACM0
ISPSPEED   = 

MCU_TARGET = atmega328p
LDSECTIONS = -Wl,--section-start=.text=0x3e00 -Wl,--section-start=.version=0x3ffe

# Build environments
# Start of some ugly makefile-isms to allow optiboot to be built
# in several different environments.  See the README.TXT file for
# details.

# default
fixpath = $(1)

GCCROOT = /usr/bin/
AVRDUDE_CONF = -C/etc/avrdude/avrdude.conf

# End of build environment code.


# The lock bits should be 0xff instead of 0x3f (to
# unlock the bootloader section) and 0xcf instead of 0x0f (to
# lock it), but since the high two bits of the lock byte are
# unused, avrdude would get confused.

ISPFUSES   = $(GCCROOT)avrdude $(AVRDUDE_CONF) -c $(ISPTOOL) \
             -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
             -e -u -U lock:w:0xff:m -U efuse:w:0x$(EFUSE):m \
             -U hfuse:w:0x$(HFUSE):m -U lfuse:w:0x$(LFUSE):m
ISPFLASH   = $(GCCROOT)avrdude $(AVRDUDE_CONF) -c $(ISPTOOL) \
             -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
             -U flash:w:$(PROGRAM)_$(TARGET).hex -U lock:w:0xcf:m

OBJ        = $(PROGRAM).o
OPTIMIZE   = -Os -fno-inline-small-functions -fno-split-wide-types #-mshort-calls

DEFS       = 
LIBS       =

CC         = $(GCCROOT)avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS  = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS = $(LDSECTIONS) -Wl,--relax -Wl,--gc-sections -nostartfiles -nostdlib

OBJCOPY    = $(GCCROOT)avr-objcopy
OBJDUMP    = $(call fixpath,$(GCCROOT)avr-objdump)

SIZE       = $(GCCROOT)avr-size

# 20MHz clocked platforms
#
# These are capable of 230400 baud, or 115200 baud on PC (Arduino Avrdude issue)
#

# ATmega168
#
atmega168: TARGET = atmega168
atmega168: MCU_TARGET = atmega168
atmega168: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
atmega168: AVR_FREQ = 16000000L 
atmega168: $(PROGRAM)_atmega168.hex
atmega168: $(PROGRAM)_atmega168.lst

atmega168_isp: atmega168
atmega168_isp: TARGET = atmega168
# 2.7V brownout
atmega168_isp: HFUSE = DD
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega168_isp: LFUSE = FF
# 512 byte boot
atmega168_isp: EFUSE = 04
atmega168_isp: isp

# ATmega328p
#
atmega328p: TARGET = atmega328p
atmega328p: MCU_TARGET = atmega328p
atmega328p: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
atmega328p: AVR_FREQ = 16000000L
atmega328p: LDSECTIONS  = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega328p: $(PROGRAM)_atmega328p.hex
atmega328p: $(PROGRAM)_atmega328p.lst

atmega328p_isp: atmega328p
atmega328p_isp: TARGET = atmega328
atmega328p_isp: MCU_TARGET = atmega328p
# 512 byte boot, SPIEN
atmega328p_isp: HFUSE = DE
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328p_isp: LFUSE = FF
# 2.7V brownout
atmega328p_isp: EFUSE = FD
atmega328p_isp: isp

# ATmega8
#
atmega8: TARGET = atmega8
atmega8: MCU_TARGET = atmega8
atmega8: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
atmega8: AVR_FREQ = 16000000L 
atmega8: LDSECTIONS  = -Wl,--section-start=.text=0x1e00 -Wl,--section-start=.version=0x1ffe
atmega8: $(PROGRAM)_atmega8.hex
atmega8: $(PROGRAM)_atmega8.lst

atmega8_isp: atmega8
atmega8_isp: TARGET = atmega8
atmega8_isp: MCU_TARGET = atmega8
# SPIEN, CKOPT, Bootsize=512B
atmega8_isp: HFUSE = CC
# 2.7V brownout, Low power xtal (16MHz) 16KCK/14CK+65ms
atmega8_isp: LFUSE = BF
atmega8_isp: isp

# ATmega88
#
atmega88: TARGET = atmega88
atmega88: MCU_TARGET = atmega88
atmega88: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
atmega88: AVR_FREQ = 16000000L 
atmega88: LDSECTIONS  = -Wl,--section-start=.text=0x1e00 -Wl,--section-start=.version=0x1ffe
atmega88: $(PROGRAM)_atmega88.hex
atmega88: $(PROGRAM)_atmega88.lst

atmega88_isp: atmega88
atmega88_isp: TARGET = atmega88
atmega88_isp: MCU_TARGET = atmega88
# 2.7V brownout
atmega88_isp: HFUSE = DD
# Low power xtal (16MHz) 16KCK/14CK+65ms
atemga88_isp: LFUSE = FF
# 512 byte boot
atmega88_isp: EFUSE = 04
atmega88_isp: isp


# 8MHz clocked platforms
#
# These are capable of 115200 baud
#

# ATmega328p @8MHz
#
atmega328p_8Mhz: TARGET = atmega328p_8MHz
atmega328p_8Mhz: MCU_TARGET = atmega328p
atmega328p_8Mhz: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
atmega328p_8Mhz: AVR_FREQ = 8000000L
atmega328p_8Mhz: LDSECTIONS = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega328p_8Mhz: $(PROGRAM)_atmega328p_8MHz.hex
atmega328p_8Mhz: $(PROGRAM)_atmega328p_8MHz.lst

atmega328p_8Mhz_isp: atmega328p_8Mhz
atmega328p_8Mhz_isp: TARGET = atmega328_8MHz
atmega328p_8Mhz_isp: MCU_TARGET = atmega328p
# 512 byte boot, SPIEN
atmega328p_8Mhz_isp: HFUSE = DF
# Internal RC oscillator (8MHz)
atmega328p_8Mhz_isp: LFUSE = E2
# 2.7V brownout
atmega328p_8Mhz_isp: EFUSE = FF
atmega328p_8Mhz_isp: isp


# ATmega328 @8MHz
#
atmega328_8Mhz: TARGET = atmega328_8MHz
atmega328_8Mhz: MCU_TARGET = atmega328
atmega328_8Mhz: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
atmega328_8Mhz: AVR_FREQ = 8000000L
atmega328_8Mhz: LDSECTIONS = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega328_8Mhz: $(PROGRAM)_atmega328_8MHz.hex
atmega328_8Mhz: $(PROGRAM)_atmega328_8MHz.lst

atmega328_8Mhz_isp: atmega328_8Mhz
atmega328_8Mhz_isp: TARGET = atmega328_8MHz
atmega328_8Mhz_isp: MCU_TARGET = atmega328
# 512 byte boot, SPIEN
atmega328_8Mhz_isp: HFUSE = DF
# Internal RC oscillator (8MHz)
atmega328_8Mhz_isp: LFUSE = E2
# 2.7V brownout
atmega328_8Mhz_isp: EFUSE = FF
atmega328_8Mhz_isp: isp

# 1MHz clocked platforms
#
# These are capable of 9600 baud
#

# ATmega328p @1MHz
#
atmega328p_1Mhz: TARGET = atmega328p_1MHz
atmega328p_1Mhz: MCU_TARGET = atmega328p
atmega328p_1Mhz: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=9600'
atmega328p_1Mhz: AVR_FREQ = 1000000L
atmega328p_1Mhz: LDSECTIONS = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega328p_1Mhz: $(PROGRAM)_atmega328p_1MHz.hex
atmega328p_1Mhz: $(PROGRAM)_atmega328p_1MHz.lst

atmega328p_1Mhz_isp: atmega328p_1Mhz
atmega328p_1Mhz_isp: TARGET = atmega328_1MHz
atmega328p_1Mhz_isp: MCU_TARGET = atmega328p
# 512 byte boot, SPIEN
atmega328p_1Mhz_isp: HFUSE = DF
# Internal RC oscillator (1MHz)
atmega328p_1Mhz_isp: LFUSE = 62
# 2.7V brownout
atmega328p_1Mhz_isp: EFUSE = FF
atmega328p_1Mhz_isp: isp


# ATmega328 @1MHz
#
atmega328_1Mhz: TARGET = atmega328_1MHz
atmega328_1Mhz: MCU_TARGET = atmega328
atmega328_1Mhz: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=9600'
atmega328_1Mhz: AVR_FREQ = 1000000L
atmega328_1Mhz: LDSECTIONS = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega328_1Mhz: $(PROGRAM)_atmega328_1MHz.hex
atmega328_1Mhz: $(PROGRAM)_atmega328_1MHz.lst

atmega328_1Mhz_isp: atmega328_1Mhz
atmega328_1Mhz_isp: TARGET = atmega328_1MHz
atmega328_1Mhz_isp: MCU_TARGET = atmega328
# 512 byte boot, SPIEN
atmega328_1Mhz_isp: HFUSE = DF
# Internal RC oscillator (1MHz)
atmega328_1Mhz_isp: LFUSE = 62
# 2.7V brownout
atmega328_1Mhz_isp: EFUSE = FF
atmega328_1Mhz_isp: isp

#
# Generic build instructions
#
#
isp: $(TARGET)
	$(ISPFUSES)
	$(ISPFLASH)

%.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(SIZE) $@

clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O binary $< $@
