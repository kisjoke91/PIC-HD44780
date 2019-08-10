/*******************************************************************************
	
	Author:		Chaos Developing
	Date:		2015-02-15
	Compiler:	avr-gcc
	Info:		HD44780 LCD Vezérl? program

*******************************************************************************/

#include "lcd.h"

//============================== EN jel kiadása ================================
static void lcd_enable()
{
    LCD_PORT |= (1<<LCD_EN);     // Enable értéke 1
    __delay_us( LCD_ENABLE_US );  // rövid szünet
    LCD_PORT &= ~(1<<LCD_EN);    // Enable törlése
}


//========================== 4 bites kimeneti m?velet ==========================
static void lcd_out( uint8_t data )
{
    data &= 0xF0;                       // fels? 4 Bit maszkolása
 
    LCD_PORT &= ~(0xF0>>(4));    // maszk törlés
    LCD_PORT |= (data>>(4));     // Bitek értékadása
    lcd_enable();
}


//==== LCD inicializálása. Az LCD használata el?tt egyszer le kell futtatni ====
void lcd_init( void )
{
    // PIN-ek konfigurálása digital IO-ként
    ANSEL = 0x00;
    
    // Használt PIN-ek kimenetre állítása
         // Enable vezeték
    LCD_DDR = 0x00;
 
    // Minden kimenet 0-ra állítása
    LCD_PORT = 0x00;
 
    // Vár az LCD feléledésére
    __delay_ms( LCD_BOOTUP_MS );
 
    // Soft-Reset 3x egymás után. 
    lcd_out( LCD_SOFT_RESET );
    __delay_ms( LCD_SOFT_RESET_MS1 );
 
    lcd_enable();
    __delay_ms( LCD_SOFT_RESET_MS2 );
 
    lcd_enable();
    __delay_ms( LCD_SOFT_RESET_MS3 );
 
    // 4-bites mód kiválasztása 
    lcd_out( LCD_SET_FUNCTION |
             LCD_FUNCTION_4BIT );
    __delay_ms( LCD_SET_4BITMODE_MS );
 
    // 4-bites mód / 2 sor / 5x7
    lcd_command( LCD_SET_FUNCTION |
                 LCD_FUNCTION_4BIT |
                 LCD_FUNCTION_2LINE |
                 LCD_FUNCTION_5X7 );
 
    // Kijelz? be / Kurzor ki / Villogás ki
    lcd_command( LCD_SET_DISPLAY |
                 LCD_DISPLAY_ON |
                 LCD_CURSOR_OFF |
                 LCD_BLINKING_OFF); 
 
    // Kurzor növekv? / Nincs görgetés
    lcd_command( LCD_SET_ENTRY |
                 LCD_ENTRY_INCREASE |
                 LCD_ENTRY_NOSHIFT );
 	// Kijelz? törlése
    lcd_clear();
}


//============================= Egy adatbájt küldése ===========================
void lcd_data( uint8_t data )
{
    LCD_PORT |= (1<<LCD_RS);    // RS 1
 
    lcd_out( data );            // els?zör a fels?, 
    lcd_out( data<<4 );         // majd az alsó 4 Bit küldése
 
    __delay_us( LCD_WRITEDATA_US );
}


//========================== Parancs küldése az LCD-re =========================
void lcd_command( uint8_t data )
{
    LCD_PORT &= ~(1<<LCD_RS);    // RS 0
 
    lcd_out( data );             // zuerst a fels?, 
    lcd_out( data<<4 );          // majd az alsó 4 Bit küldése
 
    __delay_us( LCD_COMMAND_US );
}


//========================== Kijelz? tartalmának törlése =======================
void lcd_clear( void )
{
    lcd_command( LCD_CLEAR_DISPLAY );
    __delay_ms( LCD_CLEAR_DISPLAY_MS );
}
 

//========================== Kurzor Home parancs küldése =======================
void lcd_home( void )
{
    lcd_command( LCD_CURSOR_HOME );
    __delay_ms( LCD_CURSOR_HOME_MS );
}


//====================== Kurzor tetsz?leges pozícióba ugrik ====================
void lcd_setcursor(uint8_t y, uint8_t x )
{
    uint8_t data;
 
    switch (y)
    {
        case 1:    // 1. sor
            data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
            break;
 
        case 2:    // 2. sor
            data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
            break;
 
        case 3:    // 3. sor
            data = LCD_SET_DDADR + LCD_DDADR_LINE3 + x;
            break;
 
        case 4:    // 4. sor
            data = LCD_SET_DDADR + LCD_DDADR_LINE4 + x;
            break;
 
        default:
            return;  // Rossz sor esetén
    }
 
    lcd_command( data );
}


//========= Karakterlánc kiíratása az aktuális kurzorpozíciótól kezdve =========
void lcd_string( const char *data )
{
    while( *data != '\0' )
    {   
        lcd_data(*data++);
    }
    
    
}


//========================== Egyéni karakter definiálása =======================
void lcd_generatechar( uint8_t code, const uint8_t *data )
{
    // Karakter címének beállítása
    lcd_command( LCD_SET_CGADR | (code<<3) );
 
    // Bitminta átvitele
    for ( uint8_t i=0; i<8; i++ )
    {
        lcd_data( data[i] );
    }
    
    lcd_command(LCD_SET_DDADR);
}


//====================== töröl egy sort az adott oszloptól  ====================
void lcd_clearrow(unsigned char x, unsigned char y)
{
    lcd_setcursor(x,y);
    unsigned char i = x;
    while(i < 16)
    {
        lcd_string(" ");
        __delay_us(1);
        i++;
    }
    lcd_setcursor(x,y);
}


//=================== Kiír egy decimális számot a kijelz?re ====================
void lcd_decimal(long int number)
{
    unsigned char buffer[16];
    sprintf(buffer, "%ld", number);
    lcd_string(buffer);
}

//==================== Kitöröl egy karaktert a megadot pozición ================
void lcd_clearchar(unsigned char x, unsigned char y)
{
    lcd_setcursor(x,y);
    lcd_string(" ");
}
