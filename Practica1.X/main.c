#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdbool.h>

//Seleccionador de problemas
//#define PROB1
#define PROB2
//#define PROBOR
//=============================================================================
// CONFIGURACI N DE BITS DE CONFIGURACI N (FUSES)
//=============================================================================

// Selecci n de oscilador (usar XT si est s usando un cristal de 4 MHz)
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
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

void main(void){
    TRISD = 0b00000000; // Puerto D (entrada o salida) --> d7d6d5d4d3d2d1d0
                        // 0b --> Num en binario
                        // 0 --> Salida, 1 --> entrada
    
    /*
     * TRISD = 0; // SERIA LO MISMO QUE ARRIBA (POR EL 0 DECIMAL)
     * 
    */
    
    // sE SUELE MANDAR UN VALOR BAJO A LAS SALIDAS (PARA ELIMINAR VOLT. PARASITOS)
    PORTD = 0; // ES IGUAL A 0b00000000
    
    #ifdef PROB1
    int orig = 2;   
    
    bool flag = false;
    bool subida = true;
    bool bajada = false;
    
    while(1){
        // Primer problema --> escalera
        
        while(subida){
            if (!flag){ // Para primer caso
                PORTD = 1;
                flag = true;
            }

            __delay_ms(100);

            PORTD = orig;
            orig = orig*2;
            
            if (orig == 128){
                bajada = true;
                subida = false;
            }
        }
        
        __delay_ms(100);
        
        while(bajada){
            PORTD = orig;
            orig = orig/2;
            
            __delay_ms(100);
            
            if (!flag){ // Para primer caso
                PORTD = 1;
                flag = true;
            }
            
            if (orig == 1){
                subida = true;
                bajada = false;
                flag = false;
            }
        }   
    }
    
    #endif // Fin del problema 1

    // Problema 2
#ifdef PROB2
    int count = 0;
    while(1){
        __delay_ms(40);
        while(count<=63){
            if(count == 0){
                PORTD = count;
                count+=1;
            }
            __delay_ms(40);
            PORTD = count;
            count +=1;
        }
        
        count = 0;
    }
#endif
    
    // Problema original
    
#ifdef PROBOR
    while(1){
        PORTD = 0xFF;
        
        __delay_ms(100);
        
        PORTD = ~PORTD;
        
        __delay_ms(100);
    }
#endif
    
}

