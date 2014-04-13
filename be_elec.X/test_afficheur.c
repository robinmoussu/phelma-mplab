//#include <htc.h>
#include <stdio.h>
#include "lcd.h"                       //mon lcd
#include <delays.h>                    // fonctions de delais
#pragma config OSC = HS, WDT = OFF

char chaine[]="";

void init(void)       					// exemple tempo+IT HITECH
	{
	TRISD = 0x00;
//	lcd_init();  						//mon lcd
//	lcd_clear();               			//mon lcd
	}


void main(void) {
	int mesure=150;
	init();				  				// voir plus haut
	lcd_goto(0); 						//lcd d�but 1�re ligne
	sprintf(chaine,"%s","Valeur mesuree");
	lcd_puts(chaine);	
	mesure=mesure*1.236;
	lcd_goto(0x40);            			//lcd origine seconde ligne : 40h = 64d
	sprintf(chaine,"%4d",mesure);		//affichage sur 4 digits en d�cimal
	lcd_puts(chaine);
	lcd_putch(' ');
	sprintf(chaine,"%s"," grammes");
	lcd_puts(chaine);
	while (1){
	}
}