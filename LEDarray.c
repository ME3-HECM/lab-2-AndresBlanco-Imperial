#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    LATA = 0; //set initial output LAT values (they may have random values when powered on)
    LATB = 0; //initialise LAT before TRIS
    LATFbits.LATF0 = 0;
    LATFbits.LATF6 = 0;
    LATG = 0;
	
    TRISA = 0; //set up TRIS registers for pins connected to LED array
	TRISB = 0;
    TRISFbits.TRISF0 = 0;
    TRISFbits.TRISF6 = 0;
    TRISG = 0;
    
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin    
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
    //some code to turn on/off the pins connected to the LED array
	if (number & 0b00000001)        {LATGbits.LATG0 = 1;} else {LATGbits.LATG0 = 0;} //test bit 0 against bit mask and set LED
    if (number & (0b00000001 << 1)) {LATGbits.LATG1 = 1;} else {LATGbits.LATG1 = 0;} //test bit 1
    if (number & (0b00000001 << 2)) {LATAbits.LATA2 = 1;} else {LATAbits.LATA2 = 0;} //...
    if (number & (0b00000001 << 3)) {LATFbits.LATF6 = 1;} else {LATFbits.LATF6 = 0;}
    if (number & (0b00000001 << 4)) {LATAbits.LATA4 = 1;} else {LATAbits.LATA4 = 0;}
    if (number & (0b00000001 << 5)) {LATAbits.LATA5 = 1;} else {LATAbits.LATA5 = 0;}
    if (number & (0b00000001 << 6)) {LATFbits.LATF0 = 1;} else {LATFbits.LATF0 = 0;}
    if (number & (0b00000001 << 7)) {LATBbits.LATB0 = 1;} else {LATBbits.LATB0 = 0;}
    if (number & (0b00000001 << 8)) {LATBbits.LATB1 = 1;} else {LATBbits.LATB1 = 0;} //test bit 8
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{
	unsigned int disp_val;
    
    disp_val = number*10;
	
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array

	LEDarray_disp_bin(disp_val); 	//display value on LED array
}


/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max)
{
	unsigned int disp_val;
	
	// some code to format the variable cur_val and max, store in disp_val for display on the LED array
	// hint: one method is to manipulate the variables separately and then combine them using the bitwise OR operator

	LEDarray_disp_bin(disp_val);	//display value on LED array
}
/************************************
/ Button_init
/ Function used to initialize button press bits
************************************/
void Button_init(void){
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin 
}
/************************************
/ Input_Button
/ Function used to return a 1 or 0 depending on button press
************************************/
int Input_Button(void)
{
    if (PORTFbits.RF2){
        return 0;
    }
    else {
        return 1;
    }
}
/************************************
/ LED_Light_Meter
/ Function used to create a scale for the LED array
/ Ambient light is 511 (LED array full) 
/ Thumb over the LDR is 0 (LED array empty) 
************************************/
unsigned int LED_Light_Meter(unsigned int max_light, unsigned int min_light, unsigned int light_value){
    unsigned int LED_value;
    unsigned int resolution;
    unsigned int num;
    //create ratio between max light and min light to get how much each step is in terms of value
    resolution = (max_light-min_light)/9;

    LED_value = 0;    
    
    if (light_value>max_light){
        LED_value = 511;
    }
    else{
        num = 0;
        while(num<=9){
            if (resolution*num < ((light_value-min_light)/max_light)){
            LED_value<<=num;
            LED_value += 1; 
           }
        }
    } 
    
    return LED_value;
}