//#include <xc.h>
//
//volatile unsigned long milliseconds = 0;
//
//void Timer0_Init(void) {
//    // Set up Timer0 as a 16-bit timer
//    T0CON1bits.T0CS = 0b010;  // Select FOSC/4 as clock source
//    T0CON1bits.T0CKPS = /* Appropriate prescaler value */;
//    T0CON0bits.T016BIT = 1;   // 16-bit mode
//
//    // Load Timer0 registers such that it overflows every 1 ms
//    TMR0H = /* High byte of preload value */;
//    TMR0L = /* Low byte of preload value */;
//
//    // Clear Timer0 interrupt flag
//    PIR0bits.TMR0IF = 0;
//    // Enable Timer0 interrupt
//    PIE0bits.TMR0IE = 1;
//
//    // Enable Timer0
//    T0CON0bits.T0EN = 1;
//}
//unsigned long createTime(void) {
//    return milliseconds;
//}
