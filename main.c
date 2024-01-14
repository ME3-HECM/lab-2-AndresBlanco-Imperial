#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
	unsigned int count = 0b000000001; //start at one so binary can be shifted with each iteration
    int direction = 1; //1 for forward, -1 backwards, start at forward direction
    LEDarray_init();
  
    while (1) {
		if (direction>0){              
            count <<= 1; //shift the binary number left with each increment   
        }
        
            else {
                count >>= 1;
            }
        LEDarray_disp_bin(count); //output a on the LED array in binary
        
        //check for direction
        if (count >= 511 & direction == 1) { //if count is above maximum and direction is still forward then switch direction
            direction = -1;
        }
        
        if (count <= 1 & direction ==-1) { //if count is below minimum and direction is still backwards then switch direction
            direction = 1;
        }
		__delay_ms(50); // Delay so human eye can see change
    }
}
