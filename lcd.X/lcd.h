
#ifndef __LCD_H__
#define __LCD_H__

#define _XTAL_FREQ 8000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//  LCD DB4-DB7 <-->  PORTD Bit RC0-RC3
#define LCD_PORT      PORTC
#define LCD_DDR       TRISC
 
//  LCD RS      <-->  PORTD Bit RC4     (RS: 1=Data, 0=Command)
#define LCD_RS        4
 
//  LCD EN      <-->  PORTD Bit RC5     (EN: 1-Impuls for Data)
#define LCD_EN        5


//========= Fut�si id?k: MS = miliszekundum, US = mikroszekundum) ==============

#define LCD_BOOTUP_MS           15
#define LCD_ENABLE_US           20
#define LCD_WRITEDATA_US        46
#define LCD_COMMAND_US          42
 
#define LCD_SOFT_RESET_MS1      5
#define LCD_SOFT_RESET_MS2      1
#define LCD_SOFT_RESET_MS3      1
#define LCD_SET_4BITMODE_MS     5
 
#define LCD_CLEAR_DISPLAY_MS    2
#define LCD_CURSOR_HOME_MS      2


/*====================== Az LCD sorainak defini�l�sa ============================
Az itt megadott �rt�kek 4 X 16 karatkeres kijelz? eset�n �rv�nyesek.
M�s kijelz? m�ret eset�n a m�rethez tartoz� �rt�kek ker�lnek ide
*/

#define LCD_DDADR_LINE1         0x00
#define LCD_DDADR_LINE2         0x40
#define LCD_DDADR_LINE3         0x10
#define LCD_DDADR_LINE4         0x50


//=============================== Kezel? rutinok ================================

// LCD inicializ�l�sa. Az LCD haszn�lata el?tt egyszer le kell futtatni
void lcd_init( void );

 
// kijelz? tartalm�nak t�rl�se
void lcd_clear( void );
 

// Kurzor a bal fels? sarokba ugrik
void lcd_home( void );
 

// Kurzor tetsz?leges poz�ci�ba ugrik
void lcd_setcursor( uint8_t sor, uint8_t oszlop );
 

// Egyetlen karakter ki�rat�sa az aktu�lis kurzor poz�ci�ba
void lcd_data( uint8_t data );
 

// Karakterl�nc ki�rat�sa az aktu�lis kurzorpoz�ci�t�l kezdve
void lcd_string( const char *data );
 

/*  Egy�ni karakter defini�l�sa
	A data egy t�mbre[7] kell mutasson, ami defini�lja a karaktert
*/
void lcd_generatechar( uint8_t code, const uint8_t *data );
 

// Elk�ld egy parancsot az LCD -nek
void lcd_command( uint8_t data );
 

// t�r�l egy sort az adott oszlopt�l 
void lcd_clearrow(unsigned char x, unsigned char y);


// Kit�r�l egy karaktert a megadot pozici�n
void lcd_clearchar(unsigned char x,unsigned char y);


// Ki�r egy decim�lis sz�mot a kijelz?re
void lcd_decimal(long int number);

//=============== LCD utas�t�sok. Az lcd_command argumentumai ==================

// Kijelz? t�rl�se -------------- 0b00000001
#define LCD_CLEAR_DISPLAY       0x01
 
// Kurzor bal fels? sarokba------ 0b0000001x
#define LCD_CURSOR_HOME         0x02
 
// Beviteli m�d be�ll�t�sa ------ 0b000001xx
#define LCD_SET_ENTRY           0x04
 
#define LCD_ENTRY_DECREASE      0x00
#define LCD_ENTRY_INCREASE      0x02
#define LCD_ENTRY_NOSHIFT       0x00
#define LCD_ENTRY_SHIFT         0x01
 
// Kijelz? be�ll�t�sa ----------- 0b00001xxx
#define LCD_SET_DISPLAY         0x08
 
#define LCD_DISPLAY_OFF         0x00
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_OFF          0x00
#define LCD_CURSOR_ON           0x02
#define LCD_BLINKING_OFF        0x00
#define LCD_BLINKING_ON         0x01
 
// Eltol�s be�ll�t�sa ----------- 0b0001xxxx
#define LCD_SET_SHIFT           0x10
 
#define LCD_CURSOR_MOVE         0x00
#define LCD_DISPLAY_SHIFT       0x08
#define LCD_SHIFT_LEFT          0x00
#define LCD_SHIFT_RIGHT         0x04
 
// M?k�d�s be�ll�t�sa ----------- 0b001xxxxx
#define LCD_SET_FUNCTION        0x20
 
#define LCD_FUNCTION_4BIT       0x00
#define LCD_FUNCTION_8BIT       0x10
#define LCD_FUNCTION_1LINE      0x00
#define LCD_FUNCTION_2LINE      0x08
#define LCD_FUNCTION_5X7        0x00
#define LCD_FUNCTION_5X10       0x04
 
#define LCD_SOFT_RESET          0x30
 
// CG RAM Address be�ll�t�sa ---- 0b01xxxxxx  (Character Generator RAM)
#define LCD_SET_CGADR           0x40
 
#define LCD_GC_CHAR0            0
#define LCD_GC_CHAR1            1
#define LCD_GC_CHAR2            2
#define LCD_GC_CHAR3            3
#define LCD_GC_CHAR4            4
#define LCD_GC_CHAR5            5
#define LCD_GC_CHAR6            6
#define LCD_GC_CHAR7            7
 
// DD RAM Addressbe�ll�t�sa------ 0b1xxxxxxx  (Display Data RAM)
#define LCD_SET_DDADR           0x80

#endif