/* adblink.c  PICkit2 Read pot RP1 with AD AN0 and blink LED DS1 */

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

void delay( char );

void main( void)
{
  TRISA.0 = 1;
  TRISC.0 = 0;
  char time;
  bit DS1_led;
  
  /* AD setup */ 
  ANSEL.0 = 1;
  ADCON1 = 0b0.001.0000; /* AD conversion clock 'fosc/8' */
  /* 
     0.x.xxxx.x.x  ADRESH:ADRESL is 10 bit left justified
     x.0.xxxx.x.x  Vref is Vdd
     x.x.0000.x.x  Channel 00 (AN0)
     x.x.xxxx.0.x  Go/!Done start later
     x.x.xxxx.x.1  Enable AD-converter
  */
  ADCON0 = 0b0.0.0000.0.1; 

  while(1)
    {
        GO=1;          /* start AD                               */
        while(GO);     /* wait for done                          */ 
        time = ADRESH; /* only using 8 MSB of ADRES (=ADRESH)    */
        /* must negate 'time' to increase blink speed            */ 
        /* when turning RP1 clockwise                            */
        time = ~time;
        DS1_led = !DS1_led; /* toggle DS1 LED-light on/off       */
        PORTC.0 = DS1_led;  
        delay(10);          /* add a minimum 10 ms delay         */
        delay(time);
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

