/*----------------------------------------------------------------------*/
/* FAT file system sample project for FatFs            (C)ChaN, 2014    */
/*----------------------------------------------------------------------*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
//#include "xitoa.h"
#include "ff.h"
#include "diskio.h"

//FUSES = {0xF7, 0x91, 0xFC};
/* ATmega1284p fuses: Low, High, Extended.
This is the fuse settings for this project. The fuse bits will be included
in the output hex file with program code. However some old flash programmers
cannot load the fuse bits from hex file. If it is the case, remove this line
and use these values to program the fuse bits. */


//BYTE Buff[4096];	/* Working buffer */

FATFS FatFs;		/* File system object for each logical drive */
FIL File;		/* File object */

volatile UINT Timer;	/* Performance timer (100Hz increment) */

/*---------------------------------------------------------*/
/* 100Hz timer interrupt generated by OC0A                 */
/*---------------------------------------------------------*/
ISR(TIMER1_COMP_vect)
{
	Timer++;            /* Performance counter for this module */
	disk_timerproc();   /* Drive timer procedure of low level disk I/O module */
}


static
void ioinit (void)
{
//	MCUCR = _BV(JTD); MCUCR = _BV(JTD);	/* Disable JTAG */
	/* Start 100Hz system timer (TC2.OC) */

//	OCR2 = F_CPU / 1024 / 100 - 1;
//	TCCR2 = 0b00001101;
//	TIMSK |= _BV(OCIE2);


  // Set 100 Hz timer

  ICR1 = F_CPU / 256 / 100 - 1; // 100 Hz

  TCCR1B |= (1<<WGM12);
  // Mode 4, CTC on OCR1A

  TIMSK1 |= (1<<ICIE1);
  //Set interrupt on compare match

  TCCR1B |= (1<<CS12);
  // set prescaler to 256 and starts the timer


//  ICR1 = 10,000 gives f = 100Hz

	sei();
}

void myprintf(char * line) {
	// on a good day we might print something here!
}

/*-----------------------------------------------------------------------*/
/* Main                                                                  */
int main (void)
{
	char line[120];
	DSTATUS ds;
	FRESULT fr;

	ioinit();				/* Initialize port settings and start system timer process */

	// not really necessary to call this necessary but this will be
	// the first sign that something is alive
	ds = disk_initialize(0);
	f_mount(&FatFs, "", 0);
	fr = f_open(&File, "test.fil", FA_READ);
	if (fr == FR_OK) {
		/* Read all lines and display it */
		while (f_gets(line, sizeof line, &File))
			myprintf(line);

		/* Close the file */
		f_close(&File);
	}

	for(;;);
}
