#include <xc.h>         // Biblioteca principal del compilador XC8

//#define CLASE
//#define PROB1
#define EJEMPLO
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

#define _XTAL_FREQ 8000000      // Frecuencia del oscilador (para __delay_ms y __delay_us)

#ifdef EJEMPLO
unsigned char patron[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Para hacer un vector de 8 espacios

void main(void){
    TRISB = 0; //Puerto B como salida  --> Filas
    TRISD = 0; // Puerto D como salida --> Columnas
    
    // PARA RESETEAR LOS PUERTOS
    PORTB = 0;
    PORTD = 0;
    
    while(1){
        for(char i = 0; i < 8; i++){ // Para ir corriendo los bits
            PORTB = 1 << i; // 1 que se corre i espacios
            PORTD = ~patron[i]; // Para ir encendiendo el valor de las filas.
            __delay_ms(5);
        }
    }
}
#endif

#ifdef CLASE
unsigned char patron[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81}; // Para hacer un vector de 8 espacios

void main(void){
    TRISB = 0; //Puerto B como salida  --> Filas
    TRISD = 0; // Puerto D como salida --> Columnas
    
    // PARA RESETEAR LOS PUERTOS
    PORTB = 0;
    PORTD = 0;
    
    while(1){
        for(char i = 0; i < 8; i++){ // Para ir corriendo los bits
            PORTB = 1 << i; // 1 que se corre i espacios
            PORTD = ~patron[i]; // Para ir encendiendo el valor de las filas.
            __delay_ms(5);
        }
    }
}
#endif


#ifdef PROB1

unsigned char patronJ[8] = {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0xFF};
unsigned char patronB[8] = {0xFF,0x81,0x81,0x82,0xFF,0x82,0x81,0xFF};
unsigned char patronE[8] = {0xFF,0x80,0x80,0x80,0xFF,0x80,0x80,0xFF};
unsigned char patronH[8] = {0x81,0x81,0x81,0x81,0xFF,0x81,0x81,0x81};



void main(void){
    TRISB = 0; //Puerto B como salida  --> Filas
    TRISD = 0; // Puerto D como salida --> Columnas
    
    // PARA RESETEAR LOS PUERTOS
    PORTB = 0;
    PORTD = 0;
    
    while(1){
        for(int i = 0; i < 50; i++){
            for(char i = 0; i < 8; i++){ // Para ir corriendo los bits
                PORTB = 1 << i; // 1 que se corre i espacios
                PORTD = ~patronJ[i]; // Para ir encendiendo el valor de las filas.
                __delay_ms(5);
            }
        }
        
        PORTB = 0;
        PORTD = 0;
        
        __delay_ms(500);
        
        for(int i = 0; i < 50; i++){
            for(char i = 0; i < 8; i++){ // Para ir corriendo los bits
                PORTB = 1 << i; // 1 que se corre i espacios
                PORTD = ~patronB[i]; // Para ir encendiendo el valor de las filas.
                __delay_ms(5);
            }
        }
        
        __delay_ms(500);
        
        PORTB = 0;
        PORTD = 0;
        
        __delay_ms(500);
        
        for(int i = 0; i < 50; i++){
            for(char i = 0; i < 8; i++){ // Para ir corriendo los bits
                PORTB = 1 << i; // 1 que se corre i espacios
                PORTD = ~patronE[i]; // Para ir encendiendo el valor de las filas.
                __delay_ms(5);
            }
        }
        
        __delay_ms(500);
        
        
        __delay_ms(500);
        
        PORTB = 0;
        PORTD = 0;
        
        __delay_ms(500);
        
        for(int i = 0; i < 50; i++){
            for(char i = 0; i < 8; i++){ // Para ir corriendo los bits
                PORTB = 1 << i; // 1 que se corre i espacios
                PORTD = ~patronH[i]; // Para ir encendiendo el valor de las filas.
                __delay_ms(5);
            }
        }
        
        __delay_ms(500);
    }
}


#endif