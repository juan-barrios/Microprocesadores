#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

//#define CLASE
#define ACT1

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
/*
 lcd 20X4 --> 20 columnas, 4 filas
 */

#ifdef CLASE
void main(void){
    LCD screen = {&PORTC, 2,3,4,5,6,7}; // LCD solo puede ir a un puerto
                                        // PORTC, RS, EN, D4, D5, D6, D7
    LCD_Init(screen); // Para comenzar LCD
    
    while(1){
        LCD_Clear();
        
        LCD_Set_Cursor(0,0); // Se posiciona en las coordenadas 0,0
        LCD_putrs(" HELLO WORLD!");
        LCD_Set_Cursor(1,0); // Fila 1 (2), columna 0
        for(char c = 'A'; c < 'Q';c++){ // Para escribir de A --> Q
            LCD_putc(c);
            __delay_ms(300);
        }
        __delay_ms(1000);
    }
}

#endif


#ifdef ACT1
// Definición de los arreglos de bytes (Bitmaps)
const unsigned char youtube_logo[8] = {
    0x1F, // 1 1 1 1 1
    0x1B, // 1 1 0 1 1
    0x19, // 1 1 0 0 1
    0x18, // 1 1 0 0 0
    0x19, // 1 1 0 0 1
    0x1B, // 1 1 0 1 1
    0x1F, // 1 1 1 1 1
    0x00  // 0 0 0 0 0
};

const unsigned char mlbb_logo[8] = {
    0x11, // 1 0 0 0 1
    0x15, // 1 0 1 0 1
    0x1F, // 1 1 1 1 1
    0x0E, // 0 1 1 1 0
    0x0A, // 0 1 0 1 0
    0x1F, // 1 1 1 1 1
    0x11, // 1 0 0 0 1
    0x00  // 0 0 0 0 0
};


bool update = true; // Para actualizar pantalla
bool flag = false; // Primer texto
/*
 * False: Primer texto
 * True: Segundo texto
 */

bool buttonPressed(bool flag){
    if(!flag){ 
        return true;
    }
    return false;
}


void main(void){
    ANSEL = 0;
    ANSELH = 0;
    
    OPTION_REG = OPTION_REG & 0b01111111;
    
    TRISC = 0;
    TRISD = 0;
    TRISB = 0xFF;
    
    PORTC = 0;
    PORTD = 0;
    
    // Para activar las interrupciones globales
    GIE = 1; // Para que __interrupt este activa todo el tiempo
    INTE = 1; // RB0 ya no es entrada digital, ahora es de interrupcion
    INTEDG = 0; // Para flanco de bajadad (por las resistencias de pull up)
    
    LCD screen = {&PORTC, 2,3,4,5,6,7}; // LCD solo puede ir a un puerto
                                        // PORTC, RS, EN, D4, D5, D6, D7
    LCD_Init(screen); // Para comenzar LCD
    
    LCD_Custom_Char(0, youtube_logo); // Lo guarda como 1
    LCD_Custom_Char(1, mlbb_logo);    // Lo guarda como 2
    
    while(1){
        if(update){
           LCD_Clear();
           if(!flag){ // Primer texto
                LCD_Set_Cursor(0,0); // Se posiciona en las coordenadas 0,0
                LCD_putrs(" Microprocesadores ");

                LCD_Set_Cursor(1,7); // Fila 3 (2), columna 0
                LCD_putc(0); // Imprime el carácter personalizado 0 (Logo YT)
                LCD_putrs(" YouTube");
            
            }else{ // Segundo texto
                LCD_Set_Cursor(0,0); // Se posiciona en las coordenadas 0,0
                LCD_putrs(" Verano ");

                LCD_Set_Cursor(1,7); // Fila 2 (3), columna 0
                LCD_putc(1); // Imprime el carácter personalizado 1 (Logo MLBB)
                LCD_putrs(" MLBB");
            } 
        }
        
        update = false; // Porque ya se actualizo (no se ha presionado boton)
    }
}



void __interrupt() ISR(void){
    if(INTF){ // flag que se activa cuando hay interrupcion externa (ya viene dentro del PIC)
        GIE = 0; // Para que la interrupcion no interrupma a la interrupcion
        
        update = true; // Boton se presiono
        
        // Funcion a ejecutar cuando interrupcion
        flag = buttonPressed(flag);
        
        GIE = 1; // Se vuelven a habilitar las interrupciones
        INTF = 0; // Para salir de la interrupcion
    }
}
#endif
