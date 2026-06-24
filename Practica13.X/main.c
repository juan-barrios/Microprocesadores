#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define ACT1
#define ACT2

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN
//=============================================================================

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

//=============================================================================
// DEFINICIONES
//=============================================================================

#define _XTAL_FREQ 8000000UL

#ifdef ACT1

// Con PR2 = 249, el máximo conteo útil del PWM es:
// 4 * (PR2 + 1) = 4 * 250 = 1000
#define PWM_MAX_DUTY 1000u

//=============================================================================
// FUNCIONES
//=============================================================================

void ADC_Init(void)
{
    // RA0/AN0 como entrada analógica
    TRISAbits.TRISA0 = 1;

    // AN0 analógico, los demás digitales
    ANSEL = 0x01;
    ANSELH = 0x00;

    // Justificación a la derecha, referencias VDD y VSS
    ADCON1 = 0x80;

    // ADC encendido, canal AN0, reloj Fosc/32
    // ADCS1:ADCS0 = 10
    // CHS3:CHS0 = 0000
    // ADON = 1
    ADCON0 = 0x81;

    __delay_ms(2);
}

unsigned int ADC_Read(unsigned char channel)
{
    // Seleccionar canal ADC
    ADCON0 &= 0xC3;                    // Limpia bits CHS3:CHS0
    ADCON0 |= ((channel & 0x0F) << 2); // Coloca canal

    // Tiempo de adquisición
    __delay_us(25);

    // Iniciar conversión
    ADCON0 |= 0x02;

    // Esperar a que termine la conversión
    while (ADCON0 & 0x02);

    // Resultado de 10 bits: ADRESH:ADRESL
    return ((unsigned int)ADRESH << 8) | ADRESL;
}

void PWM1_Init(void)
{
    // RC2/CCP1 como salida
    TRISCbits.TRISC2 = 0;

    // Periodo PWM
    // Fpwm = 8 MHz / [4 * (249 + 1) * 4] = 2 kHz
    PR2 = 249;

    // Duty inicial en 0
    CCPR1L = 0x00;

    // CCP1 en modo PWM
    // CCP1M3:CCP1M0 = 1100
    CCP1CON = 0x0C;

    // Timer2 ON, prescaler 1:4
    // T2CKPS1:T2CKPS0 = 01
    // TMR2ON = 1
    T2CON = 0x05;

    // Esperar a que Timer2 arranque correctamente
    while (!PIR1bits.TMR2IF);
}

void PWM1_SetDuty(unsigned int duty)
{
    if (duty > PWM_MAX_DUTY)
    {
        duty = PWM_MAX_DUTY;
    }

    // Los 8 bits más significativos van en CCPR1L
    CCPR1L = (unsigned char)(duty >> 2);

    // Los 2 bits menos significativos van en DC1B1:DC1B0
    CCP1CON &= 0xCF;                         // Limpia bits 5 y 4
    CCP1CON |= (unsigned char)((duty & 0x03) << 4);
}

void System_Init(void)
{
    // Limpiar puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;

    // Desactivar comparadores para evitar comportamientos inesperados
    CM1CON0 = 0x00;
    CM2CON0 = 0x00;

    ADC_Init();
    PWM1_Init();
}

//=============================================================================
// PROGRAMA PRINCIPAL
//=============================================================================

void main(void)
{
    unsigned int adc_value = 0;
    unsigned int duty = 0;

    System_Init();

    while (1)
    {
        // Leer potenciómetro en AN0
        adc_value = ADC_Read(0);

        // Convertir ADC 0-1023 a PWM 0-1000
        duty = (unsigned int)(((unsigned long)adc_value * PWM_MAX_DUTY) / 1023UL);

        // Opcional: zona muerta para apagar completamente el motor
        // cuando el potenciómetro está casi en cero.
        if (adc_value < 10)
        {
            duty = 0;
        }

        PWM1_SetDuty(duty);

        __delay_ms(10);
    }
}

#endif

#ifdef ACT2
//=============================================================================
// PINES L298N
//=============================================================================

#define L298_IN1 PORTDbits.RD0
#define L298_IN2 PORTDbits.RD1

// PWM con PR2 = 249:
// Fpwm = 8 MHz / [4 * (249 + 1) * 4] = 2 kHz
#define PWM_MAX_DUTY 1000u

// Zona muerta para apagar motor cuando el pot está casi en cero
#define ADC_DEADZONE 20u

// Duty mínimo para ayudar al motor a arrancar.
// Puedes bajarlo o quitarlo si tu motor arranca bien desde duty bajo.
#define MIN_DUTY_RUN 250u

//=============================================================================
// VARIABLES GLOBALES
//=============================================================================

volatile unsigned char direction_event = 0;
volatile unsigned char motor_direction = 0;

// motor_direction = 0 -> adelante
// motor_direction = 1 -> reversa

//=============================================================================
// INTERRUPCIÓN EXTERNA RB0/INT
//=============================================================================

void __interrupt() ISR(void)
{
    if (INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;   // Limpiar bandera de interrupción
        INTCONbits.INTE = 0;   // Deshabilitar INT temporalmente por rebote
        direction_event = 1;   // Avisar al main que hubo cambio
    }
}

//=============================================================================
// ADC
//=============================================================================

void ADC_Init(void)
{
    // RA0/AN0 como entrada
    TRISAbits.TRISA0 = 1;

    // AN0 analógico, todos los demás digitales
    ANSEL = 0x01;
    ANSELH = 0x00;

    // Justificación derecha, referencias VDD y VSS
    ADCON1 = 0x80;

    // ADC encendido, canal AN0, reloj Fosc/32
    ADCON0 = 0x81;

    __delay_ms(2);
}

unsigned int ADC_Read(unsigned char channel)
{
    ADCON0 &= 0xC3;                    // Limpiar selección de canal
    ADCON0 |= ((channel & 0x0F) << 2); // Seleccionar canal

    __delay_us(25);                    // Tiempo de adquisición

    ADCON0 |= 0x02;                    // Iniciar conversión

    while (ADCON0 & 0x02);             // Esperar fin de conversión

    return ((unsigned int)ADRESH << 8) | ADRESL;
}

//=============================================================================
// PWM CCP1 EN RC2
//=============================================================================

void PWM1_Init(void)
{
    // RC2/CCP1 como salida
    TRISCbits.TRISC2 = 0;

    // Periodo PWM
    PR2 = 249;

    // Duty inicial 0
    CCPR1L = 0x00;

    // CCP1 en modo PWM
    CCP1CON = 0x0C;

    // Timer2 encendido, prescaler 1:4
    T2CON = 0x05;

    // Esperar primer ciclo de Timer2
    PIR1bits.TMR2IF = 0;
    while (!PIR1bits.TMR2IF);
}

void PWM1_SetDuty(unsigned int duty)
{
    if (duty > PWM_MAX_DUTY)
    {
        duty = PWM_MAX_DUTY;
    }

    // 8 bits altos del duty
    CCPR1L = (unsigned char)(duty >> 2);

    // 2 bits bajos del duty
    CCP1CON &= 0xCF;
    CCP1CON |= (unsigned char)((duty & 0x03) << 4);
}

//=============================================================================
// L298N
//=============================================================================

void Motor_Stop(void)
{
    L298_IN1 = 0;
    L298_IN2 = 0;
}

void Motor_SetDirection(unsigned char direction)
{
    // Pequeña pausa antes de invertir dirección.
    // Esto evita cambiar de sentido bruscamente con el motor energizado.
    Motor_Stop();
    __delay_ms(100);

    if (direction == 0)
    {
        // Adelante
        L298_IN1 = 1;
        L298_IN2 = 0;
    }
    else
    {
        // Reversa
        L298_IN1 = 0;
        L298_IN2 = 1;
    }
}

//=============================================================================
// INTERRUPCIÓN EXTERNA RB0
//=============================================================================

void External_INT_Init(void)
{
    // RB0 como entrada
    TRISBbits.TRISB0 = 1;

    // Habilitar pull-up interno en RB0
    OPTION_REGbits.nRBPU = 0;  // Pull-ups globales PORTB habilitados
    WPUB = 0x01;               // Pull-up solo en RB0

    // Interrupción externa en flanco de bajada
    // Como el botón va a GND, al presionarlo pasa de 1 a 0
    OPTION_REGbits.INTEDG = 0;

    // Limpiar bandera y habilitar interrupción externa
    INTCONbits.INTF = 0;
    INTCONbits.INTE = 1;

    // Habilitar interrupciones globales
    INTCONbits.GIE = 1;
}

//=============================================================================
// INICIALIZACIÓN GENERAL
//=============================================================================

void System_Init(void)
{
    // Limpiar puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;

    // Desactivar comparadores
    CM1CON0 = 0x00;
    CM2CON0 = 0x00;

    // RD0 y RD1 como salidas para IN1 e IN2 del L298N
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;

    ADC_Init();
    PWM1_Init();

    Motor_SetDirection(motor_direction);

    External_INT_Init();
}

//=============================================================================
// MAIN
//=============================================================================

void main(void)
{
    unsigned int adc_value = 0;
    unsigned int duty = 0;

    System_Init();

    while (1)
    {
        // Si el botón generó interrupción, cambiar dirección
        if (direction_event)
        {
            __delay_ms(40); // Antirrebote

            if (PORTBbits.RB0 == 0)
            {
                motor_direction = !motor_direction;
                Motor_SetDirection(motor_direction);

                // Esperar a que se suelte el botón
                while (PORTBbits.RB0 == 0);
                __delay_ms(40);
            }

            direction_event = 0;
            INTCONbits.INTF = 0;
            INTCONbits.INTE = 1;
        }

        // Leer potenciómetro
        adc_value = ADC_Read(0);

        // Convertir ADC 0-1023 a PWM 0-1000
        duty = (unsigned int)(((unsigned long)adc_value * PWM_MAX_DUTY) / 1023UL);

        // Zona muerta y duty mínimo de arranque
        if (adc_value < ADC_DEADZONE)
        {
            duty = 0;
        }
        else if (duty < MIN_DUTY_RUN)
        {
            duty = MIN_DUTY_RUN;
        }

        PWM1_SetDuty(duty);

        __delay_ms(10);
    }
}

#endif