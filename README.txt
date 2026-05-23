README file for Low Pin Count Demo Board Lessons

These projects are intended for use with the Lessons in 
Chapter 3 of the Low Pin Count Demo Board User's Guide.

MPLAB WARNING:
If these lessons are programmed from within MPLAB using
the PICkit 2 as a programmer, the Demo Board Switch (SW1)
will not work.
This is because the LPC Demo Board shares the switch input
with the /MCLR-VPP signal line, which MPLAB drives after
programming from the PICkit 2.  This prevents the switch
from changing the signal at the input pin.

DEBUGGING IN MPLAB:
The PIC16F690 does not include In-Circuit-Debug functionality,
so the DIP part included with the Low Pin Count Demo Board
will not work with the PICkit 2 in debug mode.

To debug using the PIC16F690, the AC162061 - "MPLAB ICD 2
Debug Header Interface for PIC16F690" must be used.
It will also be necessary to construct a cable to connect 
the 6-pin PICkit 2 ICSP connector to the RJ-11 ICD connector
on the Header Interface.  Optionally, the AC164110 - "RJ-11
to ICSP Adapter" may be used instead.

For a list of supported devices, see the LPC Demo Board README file on the PICkit™ 2  
Starter Kit CD-ROM.  
8-pin DIP Flash Devices:  

PIC12F508 PIC12F629 PIC12F635  
PIC12F509 PIC12F675 PIC12F683  
PIC12F510  
14-pin DIP Flash Devices:  

PIC16F505 PIC16F630 PIC16F684  
PIC16F506 PIC16F676 PIC16F688  

20-pin DIP Flash Devices:  
PIC16F685 PIC16F689 PIC16F785  
PIC16F687 PIC16F690  
