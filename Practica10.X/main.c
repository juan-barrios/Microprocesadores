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

volatile unsigned int tiempo = 0;
volatile unsigned int contador = 0;
char exec[10];

void Timer1_Init(void)
{
    /*
       Timer1:
       Fosc = 8 MHz
       Fosc/4 = 2 MHz
       Tcy = 0.5 us

       Prescaler 1:8
       Tick = 4 us

       Para 10 ms:
       10 ms / 4 us = 2500 cuentas

       Precarga:
       65536 - 2500 = 63036 = 0xF63C
    */

    T1CON = 0x31;
    /*
       T1CON = 0b00110001

       bit 5-4: T1CKPS1:T1CKPS0 = 11 -> Prescaler 1:8
       bit 3:   T1OSCEN = 0 -> Oscilador Timer1 apagado
       bit 2:   T1SYNC = 0 -> No importa si usa reloj interno
       bit 1:   TMR1CS = 0 -> Reloj interno Fosc/4
       bit 0:   TMR1ON = 1 -> Timer1 encendido
    */

    /*
     63036 --> 0xF63C
     H --> 0xf6
     L --> 0x3c
     */
    TMR1H = 0xF6;
    TMR1L = 0x3C;

    TMR1IF = 0;   // Limpiar bandera de Timer1
    TMR1IE = 1;   // Habilitar interrupción de Timer1

    PEIE = 1;     // Habilitar interrupciones periféricas
    GIE = 1;      // Habilitar interrupciones globales
}

void __interrupt() ISR(void)
{
    if (TMR1IF)
    {
        contador++;

        if (contador >= 100)
        {
            tiempo++;
            contador = 0;
        }

        TMR1H = 0xF6;
        TMR1L = 0x3C;

        TMR1IF = 0;
    }
}

#ifdef CLASE
void main(void){
    Timer1_Init();
    
    // Para iniciar la pantalla con el puerto C
    LCD screen = {&PORTC, 2, 3, 4, 5,6 ,7};
    LCD_Init(screen);
    LCD_Clear();
    
    LCD_Set_Cursor(0,0);
    LCD_putrs("Tiempo: ");
    
    // Mensaje inicial
    LCD_Set_Cursor(1,0);
    LCD_putrs("00:00"); // Para que se muestre desde el segundo 0
    
    while(1){
        LCD_Set_Cursor(1,0);
        sprintf(exec,"%02u:%02u",tiempo/60,tiempo%60); // Horas y segundos
        // 02u --> Para dos digitos
        LCD_putrs(exec);
    }
}

#endif

#ifdef ACT1
void ADC_Init(){
    // Configuracion para marcar canales analogicos
    ANSEL = 0x01; // Para definir los pines analogicos (0b00000011)
    // ANS0 --> RA0
    ANSELH = 0; // Ponerlos en 0 para que todos los demas esten en digitales
    
    ADCON1 = 0x80; // Para definir el uso de Vref positiva --> Justificado a la derecha
    ADCON0 = 0x81; // Para multiples entradas analogicas
    
    // Si se quieren mas canales analogicos, modificar ANSEL
}

unsigned int ADC_Read(){
    __delay_us(5);
    GO_nDONE = 1; // Para que el PIC sepa que tiene que empezar la conversion Anal --> Digital
    while(GO_nDONE); // Para darle el tiempo al PIC de hacer la conversion
    
    return ((ADRESH<<8) + ADRESL);
}

void main(void){
    char buffer[15];
    
    ADC_Init();
    Timer1_Init();
    
    // Para iniciar la pantalla con el puerto C
    LCD screen = {&PORTC, 2, 3, 4,5 ,6 ,7};
    LCD_Init(screen);
    LCD_Clear();
    
    // Mensaje inicial
    LCD_Set_Cursor(1,11);
    LCD_putrs("00:00"); // Para que se muestre desde el segundo 0
    
    while(1){
        LCD_Set_Cursor(0,0);
        LCD_putrs("Voltaje: ");
        LCD_Set_Cursor(0,9);

        unsigned int adc_result = ADC_Read();

        unsigned int volt = (adc_result*50000)/ 1023; // Para que los decimales esten, pero sin ocupar espacio
        unsigned int part_ent = volt/10000; // Entre 10000, para separlo de la parte decimal
        unsigned int part_dec = volt%10000;

        sprintf(buffer, "%u.%u", part_ent,part_dec); // %u por unsigned int
        LCD_putrs(buffer);
        
        LCD_Set_Cursor(1,11);
        sprintf(exec,"%02u:%02u",tiempo/60,tiempo%60); // Horas y segundos
        // 02u --> Para dos digitos
        LCD_putrs(exec);
    }
}
#endif