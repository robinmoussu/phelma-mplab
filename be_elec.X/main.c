
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/


#include <p18cxxx.h>   /* C18 General Include File */
#include <adc.h>
#include <stdlib.h>
#include <delays.h>

#include <stdio.h>
//#include <lcd.h>                       //mon lcd
#pragma config OSC = INTIO67
//HS
#pragma config WDT   = OFF
#pragma config DEBUG = ON


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

char chaine[]="";

void main(void)
{
    char tmp;
    int bits = 1;
    char data;
    int mesure;

    /* < INITIALISATION CODE HERE> */

    /* Configure the oscillator for the device */
//    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */

    /* Setup analog functionality and port direction */
    TRISA = 0xFF;       // portA en entrée
    TRISB = 0xFF;       //
    TRISC = 0x0F;       // portC en entrée
    TRISD = 0x03;       // output
    LATD = 0xFF;
    LATC = 0xFF;
//    TRISD = 0x0F;

    /* A/D configaration */
//    OpenADC(ADC_FOSC_64&ADC_RIGHT_JUST&ADC_0_TAD,
//            ADC_CH0&ADC_INT_OFF&ADC_VREFPLUS_VDD&ADC_VREFMINUS_VSS,
//            0x00);

    // configure external LCD
//    lcd_init();
//    lcd_clear();

    /* < APPLICATION CODE HERE> */
//    Delay10TCYx( 5 ); // Delay for 50TCY to be sure all periferical are ready

//    data = 'a';
//    mesure=150;
//    lcd_goto(0); 						//lcd d?but 1?re ligne
//    sprintf(chaine,"%s","Valeur mesuree");
//    lcd_puts(chaine);
//    mesure=mesure*1.236;
//    lcd_goto(0x40);            			//lcd origine seconde ligne : 40h = 64d
//    sprintf(chaine,"%4d",mesure);		//affichage sur 4 digits en d?cimal
//    lcd_puts(chaine);
//    lcd_putch(' ');
//    sprintf(chaine,"%s"," grammes");

    while(1)
    {

////    static int tmp =1;
////    tmp = !tmp;
////    LATDbits.LATD2 = tmp;
//    lcd_puts(chaine);

//        int i;
//        int result;
//
//        // clear tmp buffer
//        tmp = 0x00;
//
//        // Le pic est en marche -> allume RB3
//        tmp |= 0x04;
//
//        // pause
//        for (i=0; i<1000; i++) { ; }
//
//        // clignotement sur RB3
//        bits = !bits;
//        tmp |= (bits) ? 0x08 : 0x00;

        //ConvertADC();
//        ConvertADC(); // Start conversion
//        while( BusyADC() ); // Wait for completion
//        result = ReadADC(); // Read result
//        tmp |= (result > 512) ? 0x10 : 0x00;
//
//        data++;
//        WriteDataXLCD(result); //write to LCD


//        // update tmp
//        LATD = tmp;
    }

}

