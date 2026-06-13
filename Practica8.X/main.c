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
    ANSEL = 0x03; // Para definir los pines analogicos (0b00000011)
    // ANS0 --> RA0
    // ANS1 --> RA1
    ANSELH = 0; // Ponerlos en 0 para que todos los demas esten en digitales
    
    ADCON1 = 0x80; // Para definir el uso de Vref positiva --> Justificado a la derecha
    ADCON0 = 0x01; // Para multiples entradas analogicas
    
    // Si se quieren mas canales analogicos, modificar ANSEL
}


unsigned int ADC_Read(unsigned char channel){
    __delay_us(5);
    
    // Se obtiene la informacion desde los puertos
    ADCON0 &= 0xC3; // Para asignar 0x083 a ADCON0 --> Para resetear la lectura analogica
    ADCON0 |= channel<<2; // Se sustituyen los bits del canal (0 o 1) y se recorre 2 bits para que se pueda leer
    __delay_ms(2); // Para que PIC haga el cambio
    
    // Se inicia ADC
    GO_nDONE = 1; // Para que el PIC sepa que tiene que empezar la conversion Anal --> Digital
    while(GO_nDONE); // Para darle el tiempo al PIC de hacer la conversion
    
    return ((ADRESH<<8) + ADRESL); 
}


#ifdef CLASE
void main(void){
    char buffer1[10]; // Primer entrada
    char buffer2[10]; // Segunda entrada
    
    ADC_Init();
    LCD screen = {&PORTC,2,3,4,5,6,7};
    LCD_Init(screen);
    
    while(1){
        LCD_Clear();
        
        // Primer voltaje
        LCD_Set_Cursor(0,0);
        LCD_putrs("Voltaje 1: ");
        LCD_Set_Cursor(0,11);
        
        // Leer y procesar voltaje 1
        unsigned int adc_result1 = ADC_Read(0);
        unsigned int volt1 = (adc_result1*50000)/1023;
        unsigned int ent1 = volt1/10000;
        unsigned int dec1 = volt1%10000;
        
        // Mostrar voltaje 1
        sprintf(buffer1,"%u.%u",ent1,dec1);
        LCD_putrs(buffer1);
        
        
         // Segundo voltaje
        LCD_Set_Cursor(1,0);
        LCD_putrs("Voltaje 2: ");
        LCD_Set_Cursor(1,11);
        
        // Leer y procesar voltaje 2
        unsigned int adc_result2 = ADC_Read(1);
        unsigned int volt2 = (adc_result2*50000)/1023;
        unsigned int ent2 = volt2/10000;
        unsigned int dec2 = volt2%10000;
        
        // Mostrar voltaje 2
        sprintf(buffer2,"%u.%u",ent2,dec2);
        LCD_putrs(buffer2);
        
        __delay_ms(100);
    }
}
#endif


#ifdef ACT1
/*
 * Se busca mostrar el voltaje que llega al PIC, controlado por un POT externo, conectado a RA0 y un segundo conectado a RA1
 * La primer pantalla es el voltaje que esta llegando
 * La segunda es el porcentaje respecto a 5V
 * La tercera es el valor de ADC (Tomando en cuenta que 1023 es 5V)
 * Se debe de cambiar de pantalla mediante un boton (RB0)
 * Se debe de cambiar de medicion (1 o 2) dependiendo de un segundo boton (RB1)
 */

volatile unsigned char flag_actualizar_lcd = 1;
volatile unsigned char pantalla = 0;
// Pantalla 0 --> Medicion 1; Pantalla 1 --> Medicion 2

volatile unsigned char op = 'v'; 
/*
 * v --> Voltaje
 * p --> porcentaje
 * a --> ADC
 */

// Funcion que cambia entre los 3 estados
char changeOP(char op){
    if(op == 'v') return 'p';
    if(op == 'p') return 'a';
    return 'v';
}

// Funcion que cambia entre las dos mediciones
char changeScreen(char pantalla){
    if(pantalla == 0) return 1;
    return 0;
}

void show(char channel, char op){
    char buffer[15];
    
    // Mostramos qué entrada estamos leyendo (1 o 2) en la esquina superior derecha
    LCD_Set_Cursor(0, 10);
    if(channel == 0) LCD_putrs(" (IN1)");
    else LCD_putrs(" (IN2)");

    if(op == 'v'){ // Voltaje   
        LCD_Set_Cursor(0,0);
        LCD_putrs("Voltaje: ");
        LCD_Set_Cursor(1,0);

        unsigned int adc_result = ADC_Read(channel);
        unsigned int volt = (adc_result*50000)/ 1023; 
        unsigned int part_ent = volt/10000; 
        unsigned int part_dec = volt%10000;

        sprintf(buffer, "%u.%04u V     ", part_ent, part_dec); 
        LCD_putrs(buffer);

    }else if(op == 'p'){ // porcentaje
        LCD_Set_Cursor(0,0);
        LCD_putrs("Porcentaje: "); 
        LCD_Set_Cursor(1,0);

        unsigned int adc_result = ADC_Read(channel);
        unsigned int percent = adc_result*100/1023;

        sprintf(buffer, "%u %%        ", percent); 
        LCD_putrs(buffer);

    }else{ // ADC
        LCD_Set_Cursor(0,0);
        LCD_putrs("ADC:       "); 
        LCD_Set_Cursor(1,0);

        unsigned int adc_result = ADC_Read(channel);
        sprintf(buffer, "%u          ", adc_result); 
        LCD_putrs(buffer);
    }
}

void main(void){
    char ultimo_op = 0; // Para el menu intercambiable
    char ultima_screen = 0; // Para cambiar entre mediciones
    
    ADC_Init();
    ADCON0 = 0x81;

    // Para las interrupciones
    TRISB = 0xFF;
    TRISC = 0x00;
    
    OPTION_REG = OPTION_REG & 0b01111111;
   
    GIE = 1; // Para que __interrupt este activa todo el tiempo
    INTF = 0;   // Limpiar bandera antes de habilitar
    INTE = 1; // RB0 ya no es entrada digital, ahora es de interrupcion
    INTEDG = 0; // Para flanco de bajadad (por las resistencias de pull up)
    
    // Para comenzar la pantalla
    LCD screen = {&PORTC,2,3,4,5,6,7};
    LCD_Init(screen);
    
    while(1){
        if(PORTBbits.RB1 == 0){
            __delay_ms(20); // Para evitar rebotes de los botones
            if(PORTBbits.RB1 == 0){
                pantalla = changeScreen(pantalla);
                while(PORTBbits.RB1 == 0); // Esperar a que se suelte el botón
            }
        }
        
        if(op != ultimo_op || pantalla != ultima_screen){
            LCD_Clear();
            ultimo_op = op;
            ultima_screen = pantalla;
            flag_actualizar_lcd=1;
        }
        
        show(pantalla, op);
        
        flag_actualizar_lcd = 0;
        __delay_ms(150);
    } 
}


void __interrupt() ISR(void){
    if(INTF){ // flag que se activa cuando hay interrupcion externa (ya viene dentro del PIC)
        __delay_ms(20); // Para el rebote de los botones

        if(PORTBbits.RB0 == 0){
            // Funcion a ejecutar cuando interrupcion
            op = changeOP(op);
        }
        INTF = 0; // Para salir de la interrupcion
    }
}

#endif
