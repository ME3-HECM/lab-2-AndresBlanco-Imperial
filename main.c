#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>

#include "LEDarray.h"
#include "ADC.h"


#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
    unsigned int light_value;
    unsigned int meter_value;
    unsigned int max_light = 169; //light value at ambient conditions
    unsigned int min_light = 50; //light value when thumb is above LDR
    unsigned int max_ppm;
    
    LEDarray_init();
    ADC_init();
    

    while (1) {
        light_value = ADC_getval(); //get value from light dependant resistor
        
         //get value for continuous meter from binary values
        meter_value = LED_Light_Meter(max_light, min_light, light_value);       
        
        //find current peak hold
        max_ppm = calc_max_PPM(meter_value, max_ppm);
        // Display combined peak hold and light value
        LEDarray_disp_PPM(meter_value, max_ppm);
        
        
    }
}
