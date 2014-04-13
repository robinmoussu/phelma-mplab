
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/


#include <p18cxxx.h>   /* C18 General Include File */
#include <adc.h>
#include <stdlib.h>
#include <delays.h>
#include "XLCD/xlcd.h"


#pragma config WDT   = OFF
#pragma config DEBUG = ON
#pragma config OSC   = INTIO67

// Stuff needed for lcd
void DelayFor18TCY( void )
{
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
}
void DelayPORXLCD (void)
{
    Delay1KTCYx(60); // Delay of 15ms
    // Cycles = (TimeDelay * Fosc) / 4
    // Cycles = (15ms * 16MHz) / 4
    // Cycles = 60,000
    return;
}
void DelayXLCD (void)
{
    Delay1KTCYx(20); // Delay of 5ms
    // Cycles = (TimeDelay * Fosc) / 4
    // Cycles = (5ms * 16MHz) / 4
    // Cycles = 20,000
    return;
}

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    char latb;
    int bits = 1;
    char data;

    /* < INITIALISATION CODE HERE> */

    /* Configure the oscillator for the device */
//    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */

    /* Setup analog functionality and port direction */
    TRISA = 0xFF;       // portA en entrée
    TRISB = 0x00;       // output
    TRISC = 0xFF;       // portC en entrée

    /* A/D configaration */
    OpenADC(ADC_FOSC_64&ADC_RIGHT_JUST&ADC_0_TAD,
            ADC_CH0&ADC_INT_OFF&ADC_VREFPLUS_VDD&ADC_VREFMINUS_VSS,
            0x00);

    // configure external LCD
    OpenXLCD( FOUR_BIT & LINE_5X7 );

    /* < APPLICATION CODE HERE> */
    Delay10TCYx( 5 ); // Delay for 50TCY to be sure all periferical are ready
    PORTB = 0x08;

    data = 'a';

    while(1)
    {
        int i;
        int result;
        
        // clear latb buffer
        latb = 0x00;

        // Le pic est en marche -> allume RB3
        latb &= 0xF8;

        // pause
        for (i=0; i<1000; i++) { ; }

        // clignotement sur RBO
        bits = !bits;
        latb |= bits;

        //ConvertADC();
        ConvertADC(); // Start conversion
        while( BusyADC() ); // Wait for completion
        result = ReadADC(); // Read result
        latb |= (result > 512) ? 0x04 : 0x00;
        
        data++;
//        WriteDataXLCD(result); //write to LCD

        // update latb
        LATB = latb;
    }

}

