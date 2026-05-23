/* rotateled.c  PICkit2 Lesson 3 Rotate LED light */

/*    Low pin count demo board               J1
         ___________  ___________           1 RA5
        |           \/           |          2 RA4
  +5V---|Vdd     16F690       Vss|---GND    3 RA3
     ---|RA5        RA0/AN0/(PGD)|-<-RP1    4 RC5
     ---|RA4            RA1/(PGC)|---       5 RC4
  SW1---|RA3/!MCLR/(Vpp)  RA2/INT|---       6 RC3
     ---|RC5/CCP              RC0|->-DS1    7 RA0
     ---|RC4                  RC1|->-DS2    8 RA1
  DS4-<-|RC3                  RC2|->-DS3    9 RA2
        |RC6                  RB4|         10 RC0
        |RC7               RB5/Rx|         11 RC1
        |RB7/Tx               RB6|         12 RC2
        |________________________|         13 +5V
                                           14 GND
*/

/* B Knudsen Cc5x C-compiler - not ANSI-C */
#include "16F690.h"
#pragma config |= 0x00D4
void delay10( char );

void main( void)
{
  TRISC = 0;
  char led_state = 1;

  while(1)
    {
        Carry = led_state.3;
        led_state = rl(led_state);
        PORTC = led_state;
        delay10(200);
    }
}







/* B Knudsen delay function */

void delay10( char n)
/*
  Delays a multiple of 10 milliseconds using the TMR0 timer
  Clock : 4 MHz   => period T = 0.25 microseconds
  1 IS = 1 Instruction Cycle = 1 microsecond
  error: 0.16 percent
*/
{
    char i;

    OPTION = 7;
    do  {
        i = TMR0 + 39; /* 256 microsec * 39 = 10 ms */
        while ( i != TMR0)
            ;
    } while ( --n > 0);
}

