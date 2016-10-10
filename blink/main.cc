#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>

int main() {
  DDRD |= (1<<DDB5); // RED   | Set 5th bit on PORTD (i.e. PD5) to 1 => output
  DDRD |= (1<<DDB6); // GREEN | Set 6th bit on PORTD (i.e. PD6) to 1 => output
  DDRB |= (1<<DDB1); // BLUE  | Set 1st bit on PORTB (i.e. PB1) to 1 => output

  for (;;) {
    PORTD ^= (1<<PORTD5);
    PORTD ^= (1<<PORTD6);
    PORTB ^= (1<<PORTB1);
    _delay_ms(1000);
  }
}





/*
 * BUN FUSE BITS TO SET CRYSTAL
 * avrdude -c stk500v2 -P /dev/cu.usbmodem00161782 -p atmega328p -U lfuse:w:0xff:m -U hfuse:w:0xC9:m
 * 
 * # COMPILE
 * avr-gcc -g -Os -mmcu=atmega328p -c main.cc
 * avr-gcc -g -mmcu=atmega328p -o main.elf main.o
 * avr-objcopy -j .text -j .data -O ihex main.elf main.hex
 *
 * UPLOAD
 * avrdude -c stk500v2 -P /dev/cu.usbmodem00161782 -p atmega328p # "sanity check"
 * avrdude -c stk500v2 -P /dev/cu.usbmodem00161782 -p atmega328p -U flash:w:main.hex
 */



// ARDUINO IDE AVRDUDE RESULT

//avrdude: Version 6.3, compiled on Jun 14 2016 at 19:15:19
//Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
//Copyright (c) 2007-2014 Joerg Wunsch
//
//System wide configuration file is "/Users/Leland/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino2/etc/avrdude.conf"
//User configuration file is "/Users/Leland/.avrduderc"
//User configuration file does not exist or is not a regular file, skipping
//
//    Using Port                    : /dev/cu.usbmodem1411
//    Using Programmer              : arduino
//Overriding Baud Rate          : 115200
//AVR Part                      : ATmega328P
//    Chip Erase delay              : 9000 us
//    PAGEL                         : PD7
//    BS2                           : PC2
//    RESET disposition             : dedicated
//RETRY pulse                   : SCK
//    serial program mode           : yes
//    parallel program mode         : yes
//    Timeout                       : 200
//StabDelay                     : 100
//CmdexeDelay                   : 25
//SyncLoops                     : 32
//ByteDelay                     : 0
//PollIndex                     : 3
//PollValue                     : 0x53
//Memory Detail                 :
//
//Block Poll               Page                       Polled
//Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack
//----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------
//eeprom        65    20     4    0 no       1024    4      0  3600  3600 0xff 0xff
//flash         65     6   128    0 yes     32768  128    256  4500  4500 0xff 0xff
//lfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
//hfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
//efuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
//lock           0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
//calibration    0     0     0    0 no          1    0      0     0     0 0x00 0x00
//signature      0     0     0    0 no          3    0      0     0     0 0x00 0x00
//
//Programmer Type : Arduino
//    Description     : Arduino
//    Hardware Version: 3
//Firmware Version: 4.4
//Vtarget         : 0.3 V
//    Varef           : 0.3 V
//    Oscillator      : 28.800 kHz
//    SCK period      : 3.3 us
//
//    avrdude: AVR device initialized and ready to accept instructions
//
//    Reading | ################################################## | 100% 0.01s
//
//avrdude: Device signature = 0x1e950f (probably m328p)
//avrdude: reading input file "/var/folders/25/jbdspw616hvb2h53sxps0bqh0000gn/T/buildd5ae82e677127ac286f51de66781d807.tmp/Blink.ino.hex"
//avrdude: writing flash (984 bytes):
//
//Writing | ################################################## | 100% 0.17s
//
//avrdude: 984 bytes of flash written
//avrdude: verifying flash memory against /var/folders/25/jbdspw616hvb2h53sxps0bqh0000gn/T/buildd5ae82e677127ac286f51de66781d807.tmp/Blink.ino.hex:
//    avrdude: load data flash data from input file /var/folders/25/jbdspw616hvb2h53sxps0bqh0000gn/T/buildd5ae82e677127ac286f51de66781d807.tmp/Blink.ino.hex:
//    avrdude: input file /var/folders/25/jbdspw616hvb2h53sxps0bqh0000gn/T/buildd5ae82e677127ac286f51de66781d807.tmp/Blink.ino.hex contains 984 bytes
//    avrdude: reading on-chip flash data:
//
//    Reading | ################################################## | 100% 0.13s
//
//avrdude: verifying ...
//avrdude: 984 bytes of flash verified
//
//avrdude done.  Thank you.
//
