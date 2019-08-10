#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Detect (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled

#include "lcd.h"

#define RE_A    3
#define RE_B    4
#define RE_OK   5
#define RET_PLUS    1
#define RET_MINUS    2
#define RET_OK   0
#define RET_NOPE   3

static uint8_t prev = 0;
static uint8_t curr = 0;

uint8_t encoder_read( void )
{ 
  uint8_t vl=0; 

  if(!(PORTA & (1 << RE_A))) vl |= (1 << 0); 
  if(!(PORTA & (1 << RE_B))) vl |= (1 << 1); 

  return vl;
}

uint8_t encoder_get(void)
{   
    curr = encoder_read();
    
    if (curr == prev) return RET_NOPE;
    
    else
    {
         if(!(curr & 0x01) && (prev & 0x01))
         {
             if(curr & 0x02) return RET_PLUS;
             else return RET_MINUS;
         }
    }
    
    prev = curr;
}

int main(int argc, char** argv) {

    int i = 0;
    lcd_init();
    
    lcd_setcursor(1,0);
    lcd_string("  CableCounter  ");
    
    TRISA |= (1<< RE_A) | (1<< RE_B) | (1<< RE_OK); 
    
    while(1)
    {
        switch(encoder_get())
        {
            case RET_NOPE:
                break;
                
            case RET_PLUS:
                i++;
                break;
                
            case RET_MINUS:
                i--;
                break;
        }
        lcd_clearrow(3,0);
        lcd_decimal(i);
        __delay_ms(1000);
    }
}
