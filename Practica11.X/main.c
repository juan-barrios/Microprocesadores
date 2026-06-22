#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//#define ACT1
/*
 * Se utiliza Timer 2
 * Se controla mediante harware
 */
#define ACT2
/*
 * Se utiliza Timer1 + interrupciones 
 * Se controla mediante software
 */

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

void ADC_Init(){
    // Configuracion para marcar canales analogicos
    ANSEL = 0x03; // Para definir los pines analogicos (0b00000011)
    // ANS0 --> RA0
    // ANS1 --> RA1
    ANSELH = 0; // Ponerlos en 0 para que todos los demas esten en digitales
    
    // Para definir RA0 como la entrada
    TRISAbits.TRISA0 = 1;   // RA0 como entrada
    
    ADCON1 = 0x80; // Para definir el uso de Vref positiva --> Justificado a la derecha
    ADCON0 = 0x81; // Para multiples entradas analogicas
    
    // Si se quieren mas canales analogicos, modificar ANSEL
    __delay_us(20);   
}

// Funcion de PWM por hardware
void PWM1_Init(void)
{
    /*
        PWM por hardware usando CCP
        Salida PWM --> RC2/CCP1/P1A.

        Fosc --> 8 MHz:
        PR2 = 255 // Para que cada pequeno giro (0 a 1023) genere cambios
        Prescaler Timer2 = 4

        Fpwm = Fosc / [4 * (PR2 + 1) * Prescaler]
        Fpwm = 8 MHz / [4 * 256 * 4]
        Fpwm ? 1953 Hz
    */

    TRISCbits.TRISC2 = 0;     // RC2 como salida

    PR2 = 255;                // Periodo PWM

    CCPR1L = 0;               // Duty inicial = 0
    CCP1CON = 0x0C;           // CCP1 en modo PWM: CCP1M3:CCP1M0 = 1100

    PSTRCON = 0x01;           // PWM dirigido a P1A, es decir RC2

    T2CON = 0x05;
    /*
        T2CON = 0000 0101
        TOUTPS3:TOUTPS0 = 0000 -> postscaler 1:1
        TMR2ON = 1             -> Timer2 encendido
        T2CKPS1:T2CKPS0 = 01   -> prescaler 1:4
    */
}

void PWM1_SetDuty(unsigned int duty)
{
    /*
        El duty del PWM es de 10 bits.
        duty puede ir de 0 a 1023.

        Los 8 MSB van en CCPR1L.
        Los 2 LSB van en CCP1CON<5:4>.
    */

    if (duty > 1023)
    {
        duty = 1023;
    }

    CCPR1L = duty >> 2;                         // Bits 9:2
    CCP1CON = (CCP1CON & 0xCF) | ((duty & 0x03) << 4);  // Bits 1:0 en DC1B1:DC1B0
}



#ifdef ACT1
unsigned int ADC_Read(){
    __delay_us(10);
    GO_nDONE = 1; // Para que el PIC sepa que tiene que empezar la conversion Anal --> Digital
    while(GO_nDONE); // Para darle el tiempo al PIC de hacer la conversion
    
    return ((ADRESH<<8) + ADRESL);
}

void main(void)
{
    unsigned int valor_adc = 0;

    ADC_Init();
    PWM1_Init();

    while (1)
    {
        valor_adc = ADC_Read();       // Lee potenciómetro: 0 a 1023
        PWM1_SetDuty(valor_adc);      // Actualiza brillo del LED

        __delay_ms(5);                // Pequeña pausa para estabilidad
    }
}
#endif


#ifdef ACT2

#define LED2_SW PORTDbits.RD0 // RD0 como la salida para el Led 2
#define PWM_SW_STEPS 64  // Para la cantidad de "niveles" que se pueden controlar por software
volatile unsigned char pwm_sw_counter = 0;
volatile unsigned char duty_led2 = 0;

void Timer1_PWM_SW_Init(void)
{
    /*
        Timer1 para generar interrupciones cada 50 us.

        Fosc = 8 MHz
        Fosc/4 = 2 MHz
        Tcy = 0.5 us

        Prescaler = 1:1

        50 us / 0.5 us = 100 cuentas
        Precarga = 65536 - 100 = 65436 = 0xFF9C
    */

    TRISDbits.TRISD0 = 0;     // RD0 salida para LED 2
    LED2_SW = 0;

    T1CON = 0x01;
    /*
        TMR1ON = 1
        TMR1CS = 0 -> reloj interno Fosc/4
        Prescaler = 1:1
    */

    TMR1H = 0xFF;
    TMR1L = 0x9C;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

unsigned int ADC_Read(unsigned char canal)
{
    /*
        Selecciona canal ADC:
        canal = 0 -> AN0
        canal = 1 -> AN1
    */

    ADCON0 = (ADCON0 & 0xC3) | ((canal & 0x0F) << 2);

    __delay_us(20);

    GO_nDONE = 1;
    while (GO_nDONE);

    return (((unsigned int)ADRESH << 8) | ADRESL);
}

void main(void)
{
    unsigned int adc_pot1 = 0;
    unsigned int adc_pot2 = 0;

    ADC_Init();
    PWM1_Init();
    Timer1_PWM_SW_Init();

    while (1)
    {
        adc_pot1 = ADC_Read(0);     // Potenciómetro 1 en AN0
        adc_pot2 = ADC_Read(1);     // Potenciómetro 2 en AN1

        // LED 1: PWM hardware de 10 bits, valor 0 a 1023
        PWM1_SetDuty(adc_pot1);

        // LED 2: PWM software de 64 niveles, valor 0 a 64
        duty_led2 = ((unsigned int)adc_pot2 * PWM_SW_STEPS) / 1023;

        __delay_ms(5);
    }
}

// Todo el control por software se realiza mediante interrupciones
void __interrupt() ISR(void)
{
    if (PIR1bits.TMR1IF) // Interrupcion del Timer1
    {
        TMR1H = 0xFF;
        TMR1L = 0x9C;

        pwm_sw_counter++;

        if (pwm_sw_counter >= PWM_SW_STEPS) // Para apagarlo si no se ha girado lo suficiente
        {
            pwm_sw_counter = 0;
        }

        if (pwm_sw_counter < duty_led2) // Para encenderlo despues de un threshold
        {
            LED2_SW = 1;
        }
        else
        {
            LED2_SW = 0;
        }

        PIR1bits.TMR1IF = 0;
    }
}
#endif