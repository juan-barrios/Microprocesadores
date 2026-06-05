#include <xc.h>         // Biblioteca principal del compilador XC8

//#define PROB1 // 0 al 9
#define PROB2 // 0 al F


//=============================================================================
// CONFIGURACI N DE BITS DE CONFIGURACI N (FUSES)
//=============================================================================

// Selecci n de oscilador (usar XT si est s usando un cristal de 4 MHz)
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (disabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection (disabled)
#pragma config WRT = OFF        // Flash Program Memory Write Enable (disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection (disabled)

//=============================================================================
// DEFINICIONES
//=============================================================================

#define _XTAL_FREQ 8000000      


#ifdef PROB1

unsigned char conteo[10] = {0xFC, 0x60,0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};

void main(void){
    TRISB = 0; // Puerto B --> salida
    PORTB = 0; // Resetear
    
    while(1){
        for(char i = 0; i<10; i++){
            PORTB = conteo[i];
            __delay_ms(500);
        }
    }
}
#endif


#ifdef PROB2
    unsigned char conteo[16] = {0xFC, 0x60,0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E};

    void main(void){
        TRISB = 0; // Puerto B --> salida
        PORTB = 0; // Resetear

        while(1){
            for(char i = 0; i<16; i++){
                PORTB = conteo[i];
                __delay_ms(250);
            }
        }
    }
#endif


