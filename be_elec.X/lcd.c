/* ------------------------------------------------------------------------- */
/* Fonctions permettant de g�rer l'afficheur LCD en mode 4 bits              */
/* PHELMA - L. Aubard													     */
/* 04/2012																	 */
/* ------------------------------------------------------------------------- */

#include "lcd.h"
#include <delays.h>


volatile near struct {
  unsigned LCD_DATA:4;
  unsigned reserved:4;
} LCDbits; // @PORTD // port D complet dont <D7:D4> 4 bits de donn�es

#define	LCD_RS  LATCbits.LATC5 		// RS afficheur
#define	LCD_RW  LATCbits.LATC6 		// R/W afficheur
#define LCD_EN  LATCbits.LATC7 		// EN afficheur
#define	LCD_PWR LATCbits.LATC4		// alimentation de l'afficheur

/* ---------------------------------------- */
/* G�n�re une impulsion Enable              */
/* ---------------------------------------- */
void lcd_strobe(void)
	{
	LCD_EN = 1;
	LCD_EN = 0;
	}

/* ---------------------------------------- */
/* Ecrit un octet sur le LCD en mode 4 bits */
/* ---------------------------------------- */
void lcd_write(char c)
	{
	unsigned char Ln, Hn;

	Hn = PORTD & 0x90;		// Poids fort = alim.EN.R/W.RS en force EN et R/W � 0 ; alim et RS conserv�s
							// RS �tant affect� avant de lancer cette fonction !
	Ln =  c >> 4 ;			// Pr�paration 4 bits de poids fort DATA
	LCD_DATA =Hn + Ln;		// Envoi 4 premiers bits (poids fort) au LCD		
	lcd_strobe();			// impulsion EN
	Delay10TCYx(4); 		// delay 40us
	Ln = c & 0x0F;			// masuage des bits de poids fort pour ne conserver que le poids faible
	LCD_DATA = Hn + Ln;		// Envoi 4 bits de poids faible au LCD
	lcd_strobe();			// impulsion EN
	Delay10TCYx(4); 		// delay 40us
	}

/* ---------------------------------------- */
/* Clear LCD                                */
/* ---------------------------------------- */
void lcd_clear(void)
	{
	LCD_RS = 0;				// n�cessaire pour instruction clear
	lcd_write(0x1);			// instruction clear
	Delay100TCYx(20);   	//delay 2ms (>1.64ms d'apr�s notice)
	}

/* ---------------------------------------- */
/* Ecit une chaine de carcat�res sur le LCD */
/* ---------------------------------------- */
void lcd_puts(const char *s)
	{
	LCD_RS = 1;				// pour �criture dans la m�moire affichage
	while(*s != '\0')
		lcd_write(*s++);
	}

/* ---------------------------------------- */
/* Ecrit un caract�re sur le LCD            */
/* ---------------------------------------- */
void lcd_putch(char c)
	{
	LCD_RS = 1;				// pour �criture dans la m�moire affichage
	lcd_write(c);
	}

/* ---------------------------------------- */
/* Go to the specified position             */
/* ---------------------------------------- */
void lcd_goto(unsigned char pos)
	{
	LCD_RS = 0;
	lcd_write(0x80+pos);	// 0x80 car adresse sur 7 bits (8�me bit � 1 voir instruction "set DDRAM")
							// pos et 0x00 pour d�but de 1�re ligne
							// pos et 0x40 pour d�but de 2�me ligne 
							// avec 16 caract�res par ligne
	}

/* ---------------------------------------- */
/* initialise the LCD en mode 4 bits        */
/* ---------------------------------------- */
void lcd_init()
	{
	LCD_RS = 0;
	LCD_EN = 0;
	LCD_RW = 0;
	LCD_PWR = 1;			// alimentation de l'afficheur
	
	Delay1KTCYx(40); 		// delay 40ms
	LCD_DATA = 0x83;		// LCD_DATA=PORTD=Alim.E.RW.RS.D7.D6.D5.D4
							// Alim.E.RW.RS = 0x8 pour toute la phase d'initialisation (hors lcd_strobe)
							// d'apr�s notice on commence par �crire 0x03 dans IR soit 0x83 pour conserver l'alim
	lcd_strobe();			// impulsion sur E
	Delay100TCYx(50); 		// delay 5ms
	lcd_strobe();			// valeur de LCD_DATA inchang�e
	Delay10TCYx(10); 		// delay 100us
	lcd_strobe();			// valeur de LCD_DATA inchang�e
	Delay10TCYx(10); 		// delay 100us

	LCD_DATA = 0x82;		// d'apr�s notice
	lcd_strobe();		
	Delay10TCYx(10); 		//delay 100us

	lcd_write(0x28);		// Instruction "fonction set" 0 0 1 DL N F x x
							// DL=0 pour mode 4 bits, 1 pour mode 8bits
							// N=0 pour une ligne, 1 pour deux lignes
							// F=0 pour caract�res 5x7, 1 pour caract�res 5x10
							// x peu importe

	lcd_write(0x0F);		// Instruction "display ON/OFF" 0 0 0 0 1 D C B
							// D=0 hors fonction, 1 en fonction
							// C=0 pas de curseur, 1 curseur
							// B=0 clignotement curseur, 1 non clignotement

	lcd_write(0x01);		// instruction "clear dispaly" 0 0 0 0 0 0 0 1

	lcd_write(0x07);		// instruction "entry mode set" 0 0 0 0 0 1 I/D S
							// I/D=0 d�placement curseur � droite apr�s �criture d'un caract�re, 1 � gauche
							// S=0 affichage n'accompagne pas le curseur, 1 accompagne le curseur
	}

