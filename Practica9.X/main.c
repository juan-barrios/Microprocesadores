#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

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


/*
 * Se busca crear un videojuego que sea un personaje en un entorno 2D
 * Joystick:
 *  - x --> RA0
 *  - y --> RA1
 *  - Switch --> RB0
 * 
 * 
 * Funciones requeridas:
 * 1. Actualizar pantalla (Cada vez que el jugador mueva el joystick --> Eje x)
 * 2. Cambio de carril (Cada vez que se presione el joystick --> Eje y)
 * 3. Animacion (Se presiona el boton --> RB0)
 * 
 * Funcionamiento del joystick:
 * - El centro es (512,512)
 * - Izquierda es (1023,512)
 * - Derecha es (0,1023)
 */

volatile unsigned char flag_actualizar_lcd = 1;
volatile unsigned char estado = 0;
volatile unsigned int pos[2] = {0,0}, lastPos[2]; // (x,y)
/*
 * Estados
 * 0: Normal
 * 1: Animacion 3 veces
 */

// Personaje
const unsigned char normal[8] = {  
    0x11, // 1 0 0 0 1
    0x15, // 1 0 1 0 1
    0x1F, // 1 1 1 1 1
    0x0E, // 0 1 1 1 0
    0x0A, // 0 1 0 1 0
    0x1F, // 1 1 1 1 1
    0x11, // 1 0 0 0 1
    0x00  // 0 0 0 0 0
};

const unsigned char cambio[8] = {
    0x00,
    0x15,
    0x15,
    0x1F,
    0x0E,
    0x0A,
    0x1F,
    0x11
};

void whereToMove(unsigned int adc1, unsigned int adc2, volatile unsigned int pos[]){ // x, y --> Valores de ADC
    volatile unsigned int x = pos[0];
    volatile unsigned int y = pos[1];
    
    // Comprobacion horizontal
    if(adc1 > 600){ // Izq --> 1023
        x--;
        if(adc1 < 0){
            x = 15;
        }
    }else if(adc1 < 500){
        x++;
        if(adc1 > 15){
            x = 0;
        }
    }
    
    // Comprobacion vertical
    if(adc2 > 600){ // Up --> 1023
        y = 0;
    }else if(adc2 < 500){
        y = 1;
    }
    
    pos[0] = x;
    pos[1] = y;
}

char animation(char estado){ // Se usa con la interrupcion
    if(estado == 0) return 1;
    return 0;
}

void show(int pos[]){
    LCD_Set_Cursor(pos[0], pos[1]);
    LCD_putc(0); // Estado normal
}

void main(void){
    lastPos[0] = pos[0]; // Para comparar con posicion anterior
    lastPos[1] = pos[1];
    
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
    
    // Inicializar personaje
    LCD_Custom_Char(0, normal);  
    LCD_Custom_Char(1, cambio);
    
    while(1){
        if(lastPos[0] != pos[0] || lastPos[1] != pos[1]){
            LCD_Clear();
            lastPos[0] = pos[0];
            lastPos[1] = pos[1];
            flag_actualizar_lcd=1;
        }
        
        unsigned int adc_result1 = ADC_Read(0); // Para el valor X
        unsigned int adc_result2 = ADC_Read(1); // Para el valor Y
        
        whereToMove(adc_result1, adc_result2, pos);
        
        show(pos);
        
        
        flag_actualizar_lcd = 0;
        __delay_ms(150);
    }
}


void __interrupt() ISR(void){
    if(INTF){ // flag que se activa cuando hay interrupcion externa (ya viene dentro del PIC)
        __delay_ms(20); // Para el rebote de los botones

        if(PORTBbits.RB0 == 0){ // Si se presiona el boton de en medio
            // Funcion a ejecutar cuando interrupcion
            estado = animation(estado);
        }
        INTF = 0; // Para salir de la interrupcion
    }
}