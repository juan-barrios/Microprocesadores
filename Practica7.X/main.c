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


void ADC_Init(){
    // Configuracion para marcar canales analogicos
    ANSEL = 0x01; // Para definir los pines analogicos (0b00000001, solo ANS0 es analogico)
    // ANS0 --> RA0
    ADCON0 = 0x81; // Se hace que la Freq de muestreo sea Fosc/32 (lo recomendado)
    ADCON1 = 0x80; // Para definir el uso de Vref positiva
    
    // Si se quieren mas canales analogicos, modificar ANSEL
}


unsigned int ADC_Read(){
    __delay_us(5);
    GO_nDONE = 1; // Para que el PIC sepa que tiene que empezar la conversion Anal --> Digital
    while(GO_nDONE); // Para darle el tiempo al PIC de hacer la conversion
    
    return ((ADRESH<<8) + ADRESL);
}


#ifdef ACT1
/*
 * Se busca mostrar el voltaje que llega al PIC, controlado por un POT externo, conectado a RA0
 * La primer pantalla es el voltaje que esta llegando
 * La segunda es el porcentaje respecto a 5V
 * La tercera es el valor de ADC (Tomando en cuenta que 1023 es 5V)
 * Se debe de cambiar de pantalla mediante un boton
 */

volatile unsigned char op = 'v'; 
/*
 * v --> Voltaje
 * p --> porcentaje
 * a --> ADC
 */

// Funcion que cambia entre los 3 estados
char change(char op){
    if(op == 'v') return 'p';
    if(op == 'p') return 'a';
    return 'v';
}

void main(void){
    ADC_Init(); // Para iniciar el ADC
  
    // Para las interrupciones
    ANSELH = 0;
    
    OPTION_REG = OPTION_REG & 0b01111111;
    
    TRISB = 0xFF;
    
    GIE = 1; // Para que __interrupt este activa todo el tiempo
    INTE = 1; // RB0 ya no es entrada digital, ahora es de interrupcion
    INTEDG = 0; // Para flanco de bajadad (por las resistencias de pull up)
    
    // Para comenzar la pantalla
    LCD screen = {&PORTC,2,3,4,5,6,7};
    LCD_Init(screen);
    
    char buffer[10];
    while(1){
        LCD_Clear();
        if(op == 'v'){ // Voltaje   
            LCD_Set_Cursor(0,0);
            LCD_putrs("Voltaje: ");
            LCD_Set_Cursor(0,9);

            unsigned int adc_result = ADC_Read();

            unsigned int volt = (adc_result*50000)/ 1023; // Para que los decimales esten, pero sin ocupar espacio
            unsigned int part_ent = volt/10000; // Entre 10000, para separlo de la parte decimal
            unsigned int part_dec = volt%10000;

            sprintf(buffer, "%u.%u", part_ent,part_dec); // %u por unsigned int
            LCD_putrs(buffer);

        }else if(op == 'p'){ // porcentaje
            LCD_Set_Cursor(0,0);
            LCD_putrs("Porcentaje: "); // 12 caracteres
            LCD_Set_Cursor(0,12);

            unsigned int adc_result = ADC_Read();
            unsigned int percent = adc_result*100/1023;

            sprintf(buffer, "%u %%", percent); 
            LCD_putrs(buffer);

        }else{ // ADC
            LCD_Set_Cursor(0,0);
            LCD_putrs("ADC: "); // 5 caracteres
            LCD_Set_Cursor(0,5);

            unsigned int adc_result = ADC_Read();
            sprintf(buffer, "%u", adc_result); 
            LCD_putrs(buffer);
        }
        __delay_ms(100);
    } 
}


void __interrupt() ISR(void){
    if(INTF){ // flag que se activa cuando hay interrupcion externa (ya viene dentro del PIC)
        GIE = 0; // Para que la interrupcion no interrupma a la interrupcion
        
        // Funcion a ejecutar cuando interrupcion
        op = change(op);
        
        GIE = 1; // Se vuelven a habilitar las interrupciones
        INTF = 0; // Para salir de la interrupcion
    }
}
#endif



#ifdef CLASE
void main(void){
    ADC_Init(); // Para iniciar el ADC
    
    // Para comenzar la pantalla
    LCD screen = {&PORTC,2,3,4,5,6,7};
    LCD_Init(screen);
    
    char buffer[10];
    
    while(1){
        LCD_Clear();
        LCD_Set_Cursor(0,0);
        LCD_putrs("Voltaje: ");
        LCD_Set_Cursor(0,9);
        
        unsigned int adc_result = ADC_Read();
        
        // Consume mucha memoria --> No usar
//        float volt = adc_result*5.0/1023; // 1023 porque es el tamano maximo del PIC 2^10
//        sprintf(buffer, "%.1f", volt); // Para convertir de num a string
//        LCD_putrs(buffer);
        
        // Optimizacion
        // Considerando 5V de entrada
        unsigned int volt = (adc_result*50000)/ 1023; // Para que los decimales esten, pero sin ocupar espacio
        unsigned int part_ent = volt/10000; // Entre 10000, para separlo de la parte decimal
        unsigned int part_dec = volt%10000;
        
        sprintf(buffer, "%u.%u", part_ent,part_dec); // %u por unsigned int
        LCD_putrs(buffer);
        
        __delay_ms(200); // Tasa de actualizacion de la pantalla
    }
}

#endif