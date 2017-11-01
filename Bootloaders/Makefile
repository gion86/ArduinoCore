# Makefile for ATmegaBOOT - Optiboot bootloaders
# E.Lins, 18.7.2005
# $Id$
#
# - removed unused platforms
# - changed programmer to usbasp
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
# current path variables, but we can also build using an installed
# Arduino user IDE setup, or the Arduino source tree.
# Uncomment this next lines to build within the arduino environment,
# using the arduino-included avrgcc toolset (mac and pc)
# ENV ?= arduino
# ENV ?= arduinodev
# OS ?= macosx
# OS ?= windows


# enter the parameters for the avrdude isp tool
ISPTOOL	   = usbasp
ISPPORT	   = 
ISPSPEED   = 

MCU_TARGET = atmega328
LDSECTIONS  = -Wl,--section-start=.text=0x3e00 -Wl,--section-start=.version=0x3ffe

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

ISPFUSES    = $(GCCROOT)avrdude $(AVRDUDE_CONF) -c $(ISPTOOL) \
              -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
              -e -u -U lock:w:0x3f:m -U efuse:w:0x$(EFUSE):m \
              -U hfuse:w:0x$(HFUSE):m -U lfuse:w:0x$(LFUSE):m
ISPFLASH    = $(GCCROOT)avrdude $(AVRDUDE_CONF) -c $(ISPTOOL) \
              -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
              -U flash:w:$(PROGRAM)_$(TARGET).hex -U lock:w:0x0f:m

OBJ        = $(PROGRAM).o
OPTIMIZE = -Os -fno-inline-small-functions -fno-split-wide-types #-mshort-calls

DEFS       = 
LIBS       =

CC         = $(GCCROOT)avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS       = $(LDSECTIONS) -Wl,--relax -Wl,--gc-sections -nostartfiles -nostdlib

OBJCOPY        = $(GCCROOT)avr-objcopy
OBJDUMP        = $(call fixpath,$(GCCROOT)avr-objdump)

SIZE           = $(GCCROOT)avr-size

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

# ATmega328
#
atmega328: TARGET = atmega328
atmega328: MCU_TARGET = atmega328p
atmega328: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
atmega328: AVR_FREQ = 16000000L
atmega328: LDSECTIONS  = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega328: $(PROGRAM)_atmega328.hex
atmega328: $(PROGRAM)_atmega328.lst

atmega328_isp: atmega328
atmega328_isp: TARGET = atmega328
atmega328_isp: MCU_TARGET = atmega328p
# 512 byte boot, SPIEN
atmega328_isp: HFUSE = DE
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328_isp: LFUSE = FF
# 2.7V brownout
atmega328_isp: EFUSE = FD
atmega328_isp: isp

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

# ATmega328 @8MHz
#
atmega328_8Mhz: TARGET = atmega328_pro_8MHz
atmega328_8Mhz: MCU_TARGET = atmega328p
atmega328_8Mhz: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
atmega328_8Mhz: AVR_FREQ = 8000000L
atmega328_8Mhz: LDSECTIONS = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffe
atmega328_8Mhz: $(PROGRAM)_atmega328_8MHz.hex
atmega328_8Mhz: $(PROGRAM)_atmega328_8MHz.lst

atmega328_8Mhz_isp: atmega328_8Mhz
atmega328_8Mhz_isp: TARGET = atmega328_pro_8MHz
atmega328_8Mhz_isp: MCU_TARGET = atmega328p
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
