/* kilroy.c  PICkit2 Test interrupt SW1 and DS1 */

/*   "Low pin count demo board"              J1
         ___________  ___________           1 RA5
        |           \/           |          2 RA4
  +5V---|Vdd     16F690       Vss|---GND    3 RA3 --
     ---|RA5        RA0/AN0/(PGD)|-<-RP1    4 RC5   |
     ---|RA4            RA1/(PGC)|---       5 RC4   | insert
  SW1---|RA3/!MCLR/(Vpp)  RA2/INT|---       6 RC3   Resistor 1k 
     ---|RC5/CCP              RC0|->-DS1    7 RA0   |
     ---|RC4                  RC1|->-DS2    8 RA1   |
  DS4-<-|RC3                  RC2|->-DS3    9 RA2 --
        |RC6                  RB4|         10 RC0
        |RC7               RB5/Rx|         11 RC1
        |RB7/Tx               RB6|         12 RC2
        |________________________|         13 +5V
                                           14 GND
*/

/* Insert resistor 1k (value not critical) between J1:3 and J1:9 */  
/* for SW1 to be able to generate external interrupt             */

/* B Knudsen Cc5x C-compiler - not ANSI-C */
#include "16F690.h"
#include "int16Cxx.h"
#pragma config |= 0x00D4

#pragma origin 4
interrupt int_server( void ) /* the place for the interrupt routine */
{
  int_save_registers
  if( INTF == 1 )  /* test if it is the INT-interrupt?         */
    {              /* this time it's obvius that it is!        */
      PORTC.0 = 1; /* Lightdiode on to show "Killroy was here" */
      INTF = 0;    /* Reset INT-flag before leaving            */
    }
  int_restore_registers
}

/* include no code before the interrupt routine */
void delay( char);

void main( void)
{
  TRISC.0 = 0; /* RC0 is output  */
  PORTC.0 = 0; /* the LED is off */
  delay(10);   /* 10 ms for demo board initialization              */
               /* or uncheck !MCLR after Vdd is checked in PICkit2 */ 
  TRISA.2 = 1; /* INT is input   */
  ANSEL = 0;   /* PORTA dig i/o  */

  INTEDG  = 0;   /* interrupt on negative going edge                */
                 /* eg when you press SW1 (it's connected that way) */
  INTE    = 1;   /* local enable  */
  GIE     = 1;   /* global enable */

  while(1)
    {
      nop(); /* the LED is still off */
    }
}




/* B Knudsen delay function */

void delay( char millisec)
/* 
  Delays a multiple of 1 milliseconds at 4 MHz
  using the TMR0 timer 
*/
{
    OPTION = 2;  /* prescaler divide by 8        */
    do  {
        TMR0 = 0;
        while ( TMR0 < 125)   /* 125 * 8 = 1000  */
            ;
    } while ( -- millisec > 0);
}

