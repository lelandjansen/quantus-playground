#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include "ff.h"
#include "diskio.h"

#include "main.h"
#include "led/led.h"



void * operator new(size_t size) { return malloc(size); }
void operator delete(void * ptr) { free(ptr); }
// does this work for new[]
int __cxa_guard_acquire(__guard *g) { return !*(char *)(g); };
void __cxa_guard_release (__guard *g) { *(char *)g = 1; };
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual(void) {};


void Setup() { // replace this with a class later
  Led::instance().Setup();

  DDRB |= (1<<DDB5); // SPI_SCK
  DDRB |= (1<<DDB3); // SPI_MOSI
  DDRB &= ~(1<<DDB4); // SPI_MISO // probably don't need to do this
  DDRB |= (1<<DDB2); // pb2 must be output (otherwise spi bus will be in slave mode)

  DDRD |= (1<<DDD4); // SD_CS
  PORTD |= (1<<PORTD4);

  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0);

  sei(); // Enable interrupts
}



void SdTest() {
  DSTATUS drive_status;
  FATFS file_system;
  FIL file;

  const char text[] = "Testing 1, 2, 3...";
  unsigned int bytes_written;
  unsigned char force_mount = (unsigned char)false;

  Led::instance().Blue();

  drive_status = f_mount(&file_system, "", force_mount);

  Led::instance().Magenta();

  if ((drive_status != FR_OK) && (drive_status != FR_EXIST)) Led::instance().Red();
  else {
    Led::instance().Yellow();
    f_open(&file, "/test/test.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
    f_write(&file, text, strlen(text), &bytes_written);
    f_close(&file);
    f_sync(&file);
    f_mount(0, 0, 0); // un mount
    Led::instance().Green();
  }
}




//int main() {
//  Setup();
//
//  Led::instance().Cyan();
//
//  _delay_ms(1);
//
//  SdTest();
//
//  for(;;);
//
//  return 0;
//}












/*---------------------------------------------------------*/
/* User Provided Timer Function for FatFs module           */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support a real time clock.          */
/* This is not required in read-only configuration.        */

//BYTE RtcOk;

DWORD get_fattime(void) {
  return 0;
//  RTC rtc;
//  rtc.year = 2016;
//  rtc.month = 11;
//  rtc.mday = 12;
//  rtc.hour = 15;
//  rtc.min = 38;
//  rtc.sec = 33;
//
////  if (!RtcOk) return 0;
////
////  /* Get local time */
////  rtc_gettime(&rtc);
////
//  /* Pack date and time into a DWORD variable */
//  return ((DWORD)(rtc.year - 1980) << 25) |
//      ((DWORD)rtc.month << 21) |
//      ((DWORD)rtc.mday << 16) |
//      ((DWORD)rtc.hour << 11) |
//      ((DWORD)rtc.min << 5) |
//      ((DWORD)rtc.sec >> 1);
}

