#include <xc.h>         // Biblioteca principal del compilador XC8

#define PROB1
//#define CLASE

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

unsigned char estado1, estado2, estado3; // Para los estados de las entradas digitales

#ifdef CLASE // Enciende cada led al clickear los botones
void main(void){
    // Para convertir de analog --> digitales
    // Todos los pines son entradas digitales
    ANSEL = 0; // 8 BITS
    ANSELH = 0; // 8 BITS
    
    // El puerto B ya tiene resistencias de pull up --> NO NECESITA RESISTENCIAS PARA ENTRADAS
    
    OPTION_REG = OPTION_REG & 0b01111111; // Se cambia el bit de mayor peso (7)
    // Se activa las resistencias de pull up del puerto B
    
    TRISB = 0xFF; // Para que se activen todos los bits (Todo el puerto B es entrada)
    TRISD = 0; // Salida
    
    while(1){
        // Si se presiona el boton en n, se enciendde en m
        PORTDbits.RD0 = !PORTBbits.RB0; // Para que el valor de D0 se tome de B0
        PORTDbits.RD1 = !PORTBbits.RB1;
        PORTDbits.RD2 = !PORTBbits.RB2;
    }
}

#endif

#ifdef PROB1
void main(void){
    
    char conteo[10] = {0xFC, 0x60,0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
    ANSEL = 0; // 8 BITS
    ANSELH = 0; // 8 BITS
    OPTION_REG = OPTION_REG & 0b01111111;
    TRISB = 0xFF; 
    TRISD = 0; 
    
    
    // Puerto C --> Decenas
    TRISC = 0; // Puerto C --> salida
    PORTC = 0; // Resetear
    
    // Puerto D --> Unidades
    TRISD = 0; // Puerto D --> salida
    PORTD = 0; // Resetear
    
    int uni = 0, dec = 0;
    while(1){
        if(PORTBbits.RB2 == 1){ // Multiplicador no activo
            if(PORTBbits.RB0 == 0){ // Sumar 1
                __delay_ms(200);
                uni++;
                if(uni > 9){
                    uni = 0;
                    dec++;
                    if(dec > 9){
                        dec = 0;
                    }
                }
            }
        
            if(PORTBbits.RB1 == 0){ // Restar 1
                __delay_ms(200);
                uni--;
                if(uni < 0){
                    uni = 9;
                    
                    if(dec == 0){ // Cuando baja del 0 0 al 99
                        dec = 9;
                    }else if(dec > 0){
                        dec--; 
                    }
                }
            }
        }else{ // Multiplicador activo
            if(PORTBbits.RB0 == 0){ // Sumar 2
                __delay_ms(200);
                uni = uni + 2;
                if(uni > 9){
                    uni = uni - 10;
                    dec++;
                    if(dec > 9){
                        dec = 0;
                    }
                }
            }
        
            if(PORTBbits.RB1 == 0){ // Restar 2
                __delay_ms(200);
                uni = uni - 2;
                if(uni < 0){
                    uni = 0;
                    
                    if(dec == 0){ // Cuando baja del 0 0 al 99
                        dec = 9;
                        uni = 8;
                    }else if (dec > 0){
                        uni = uni + 10;
                        dec--;
                    }
                }
            }
        }
        
        PORTD = conteo[uni];
        PORTC = conteo[dec]; 
    } 
}
#endif