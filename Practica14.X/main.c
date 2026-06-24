#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ACT1
//#define ACT2

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

// Servo conectado en RC2, pin 17 en PIC16F887 DIP de 40 pines
#define SERVO_PIN PORTCbits.RC2
#define SERVO_TRIS TRISCbits.TRISC2

#define SERVO_MIN_US      600    // Pulso para 0 grados
#define SERVO_MAX_US      3000    // Pulso para 180 grados
#define SERVO_PERIOD_US   20000   // Periodo completo del servo: 20 ms
#define SERVO_STEP_DEG    1       // Incremento de ángulo por ciclo

#ifdef ACT1
//=============================================================================
// VARIABLES GLOBALES
//=============================================================================

volatile unsigned int servo_pulse_us = SERVO_MIN_US;
volatile unsigned char servo_angle = 0;
volatile signed char servo_direction = 1;

// 1 = estamos en la parte alta del pulso
// 0 = estamos en la parte baja del periodo
volatile unsigned char servo_phase_high = 1;

//=============================================================================
// PROTOTIPOS
//=============================================================================

void System_Init(void);
void Servo_Init(void);
void Timer1_Load_Us(unsigned int time_us);
unsigned int Servo_Angle_To_Pulse(unsigned char angle);
void Servo_Update_Angle(void);

//=============================================================================
// FUNCIÓN PRINCIPAL
//=============================================================================

void main(void)
{
    System_Init();
    Servo_Init();

    while (1)
    {
        // No se necesita interacción externa.
        // El movimiento del servo ocurre automáticamente dentro de la ISR.
    }
}

//=============================================================================
// INICIALIZACIÓN GENERAL
//=============================================================================

void System_Init(void)
{
    // Desactivar entradas analógicas para trabajar con pines digitales
    ANSEL = 0x00;
    ANSELH = 0x00;

    // Limpiar puerto C
    PORTC = 0x00;
    TRISC = 0x00;
}

//=============================================================================
// INICIALIZACIÓN DEL SERVO CON TIMER1
//=============================================================================

void Servo_Init(void)
{
    SERVO_TRIS = 0;   // RC2 como salida
    SERVO_PIN = 0;

    servo_angle = 0;
    servo_direction = 1;
    servo_pulse_us = Servo_Angle_To_Pulse(servo_angle);

    // Timer1 apagado mientras se configura
    T1CON = 0x00;

    // Timer1 con reloj interno Fosc/4 y prescaler 1:1
    // Fosc = 8 MHz -> Fosc/4 = 2 MHz -> tick = 0.5 us
    T1CONbits.TMR1CS = 0;     // Reloj interno
    T1CONbits.T1CKPS0 = 0;    // Prescaler 1:1
    T1CONbits.T1CKPS1 = 0;
    T1CONbits.T1OSCEN = 0;    // Oscilador externo de Timer1 apagado

    PIR1bits.TMR1IF = 0;      // Limpiar bandera de Timer1
    PIE1bits.TMR1IE = 1;      // Habilitar interrupción de Timer1

    INTCONbits.PEIE = 1;      // Habilitar interrupciones periféricas
    INTCONbits.GIE = 1;       // Habilitar interrupciones globales

    // Iniciar primer pulso en alto
    SERVO_PIN = 1;
    servo_phase_high = 1;
    Timer1_Load_Us(servo_pulse_us);

    T1CONbits.TMR1ON = 1;     // Encender Timer1
}

//=============================================================================
// CARGA DE TIMER1 EN MICROSEGUNDOS
//=============================================================================

void Timer1_Load_Us(unsigned int time_us)
{
    /*
     * Con Fosc = 8 MHz:
     * Fosc/4 = 2 MHz
     * 1 tick = 0.5 us
     * cuentas = tiempo_us / 0.5 = tiempo_us * 2
     */

    unsigned int counts;
    unsigned int preload;

    counts = time_us * 2;
    preload = (unsigned int)(65536UL - counts);

    TMR1H = (unsigned char)(preload >> 8);
    TMR1L = (unsigned char)(preload & 0xFF);
}

//=============================================================================
// CONVERTIR ÁNGULO A ANCHO DE PULSO
//=============================================================================

unsigned int Servo_Angle_To_Pulse(unsigned char angle)
{
    /*
     * 0 grados   -> 1000 us
     * 180 grados -> 2000 us
     */

    unsigned long pulse;

    pulse = SERVO_MIN_US;
    pulse += ((unsigned long)angle * (SERVO_MAX_US - SERVO_MIN_US)) / 180UL;

    return (unsigned int)pulse;
}

//=============================================================================
// ACTUALIZAR ÁNGULO AUTOMÁTICAMENTE
//=============================================================================

void Servo_Update_Angle(void)
{
    if (servo_direction > 0)
    {
        if ((servo_angle + SERVO_STEP_DEG) >= 180)
        {
            servo_angle = 180;
            servo_direction = -1;
        }
        else
        {
            servo_angle += SERVO_STEP_DEG;
        }
    }
    else
    {
        if (servo_angle <= SERVO_STEP_DEG)
        {
            servo_angle = 0;
            servo_direction = 1;
        }
        else
        {
            servo_angle -= SERVO_STEP_DEG;
        }
    }

    servo_pulse_us = Servo_Angle_To_Pulse(servo_angle);
}

//=============================================================================
// INTERRUPCIÓN
//=============================================================================

void __interrupt() ISR(void)
{
    if (PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;

        if (servo_phase_high)
        {
            // Terminó la parte alta del pulso
            SERVO_PIN = 0;
            servo_phase_high = 0;

            // Esperar el resto del periodo de 20 ms
            Timer1_Load_Us(SERVO_PERIOD_US - servo_pulse_us);

            // Actualizar el ángulo para el siguiente pulso
            Servo_Update_Angle();
        }
        else
        {
            // Terminó la parte baja, inicia nuevo pulso
            SERVO_PIN = 1;
            servo_phase_high = 1;

            // Mantener alto según el ángulo actual
            Timer1_Load_Us(servo_pulse_us);
        }
    }
}

#endif


#ifdef ACT2
//=============================================================================
// VARIABLES GLOBALES
//=============================================================================

volatile unsigned int servo_pulse_us = SERVO_MIN_US;
volatile unsigned char servo_phase_high = 1;

//=============================================================================
// PROTOTIPOS
//=============================================================================

void System_Init(void);
void ADC_Init(void);
unsigned int ADC_Read_AN0(void);

void Servo_Init(void);
void Timer1_Load_Us(unsigned int time_us);
unsigned int ADC_To_Servo_Pulse(unsigned int adc_value);

//=============================================================================
// MAIN
//=============================================================================

void main(void)
{
    unsigned int adc_value;
    unsigned int new_pulse;

    System_Init();
    ADC_Init();
    Servo_Init();

    while (1)
    {
        // Leer potenciómetro en AN0
        adc_value = ADC_Read_AN0();

        // Convertir ADC 0-1023 a pulso 1000-2000 us
        new_pulse = ADC_To_Servo_Pulse(adc_value);

        /*
         * Como servo_pulse_us se usa dentro de la interrupción,
         * conviene actualizarla con interrupciones deshabilitadas
         * para evitar que se lea a medias.
         */
        INTCONbits.GIE = 0;
        servo_pulse_us = new_pulse;
        INTCONbits.GIE = 1;

        // Pequeña pausa para evitar cambios demasiado bruscos
        __delay_ms(20);
    }
}

//=============================================================================
// INICIALIZACIÓN GENERAL
//=============================================================================

void System_Init(void)
{
    PORTA = 0x00;
    PORTC = 0x00;

    TRISA = 0x01;   // RA0 como entrada
    TRISC = 0x00;   // PORTC como salida

    /*
     * ANSEL controla qué pines serán analógicos.
     * ANS0 = 1 porque usaremos AN0.
     */
    ANSEL = 0x01;   // AN0 analógico, los demás digitales
    ANSELH = 0x00;  // AN8-AN13 digitales
}

//=============================================================================
// ADC
//=============================================================================

void ADC_Init(void)
{
    /*
     * ADCON1:
     * ADFM = 1 ? resultado justificado a la derecha
     * VCFG1 = 0 ? referencia negativa VSS
     * VCFG0 = 0 ? referencia positiva VDD
     */
    ADCON1bits.ADFM = 1;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;

    /*
     * ADCON0:
     * Canal AN0
     * ADC clock Fosc/32
     * ADC encendido
     */
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;

    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 1;

    ADCON0bits.ADON = 1;

    __delay_ms(2);
}

unsigned int ADC_Read_AN0(void)
{
    unsigned int result;

    // Tiempo de adquisición
    __delay_us(20);

    // Iniciar conversión
    ADCON0bits.GO_nDONE = 1;

    // Esperar a que termine
    while (ADCON0bits.GO_nDONE);

    // Resultado de 10 bits justificado a la derecha
    result = ((unsigned int)ADRESH << 8) | ADRESL;

    return result;
}

//=============================================================================
// SERVO CON TIMER1
//=============================================================================

void Servo_Init(void)
{
    SERVO_TRIS = 0;
    SERVO_PIN = 0;

    // Timer1 apagado mientras se configura
    T1CON = 0x00;

    /*
     * Timer1 con reloj interno Fosc/4.
     * Fosc = 8 MHz
     * Fosc/4 = 2 MHz
     * Tick = 0.5 us
     */
    T1CONbits.TMR1CS = 0;     // Reloj interno
    T1CONbits.T1CKPS0 = 0;    // Prescaler 1:1
    T1CONbits.T1CKPS1 = 0;
    T1CONbits.T1OSCEN = 0;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    // Iniciar señal del servo
    SERVO_PIN = 1;
    servo_phase_high = 1;
    Timer1_Load_Us(servo_pulse_us);

    T1CONbits.TMR1ON = 1;
}

void Timer1_Load_Us(unsigned int time_us)
{
    unsigned int counts;
    unsigned int preload;

    /*
     * Tick Timer1 = 0.5 us
     * counts = time_us / 0.5 = time_us * 2
     */

    counts = time_us * 2;
    preload = (unsigned int)(65536UL - counts);

    TMR1H = (unsigned char)(preload >> 8);
    TMR1L = (unsigned char)(preload & 0xFF);
}

unsigned int ADC_To_Servo_Pulse(unsigned int adc_value)
{
    unsigned long pulse;

    /*
     * adc_value: 0 a 1023
     * pulso: 1000 us a 2000 us
     */

    pulse = SERVO_MIN_US;
    pulse += ((unsigned long)adc_value * (SERVO_MAX_US - SERVO_MIN_US)) / 1023UL;

    return (unsigned int)pulse;
}

//=============================================================================
// INTERRUPCIÓN
//=============================================================================

void __interrupt() ISR(void)
{
    if (PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;

        if (servo_phase_high)
        {
            // Termina pulso alto
            SERVO_PIN = 0;
            servo_phase_high = 0;

            // Completar periodo de 20 ms
            Timer1_Load_Us(SERVO_PERIOD_US - servo_pulse_us);
        }
        else
        {
            // Inicia nuevo pulso alto
            SERVO_PIN = 1;
            servo_phase_high = 1;

            // Pulso según posición del potenciómetro
            Timer1_Load_Us(servo_pulse_us);
        }
    }
}


#endif