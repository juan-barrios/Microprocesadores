#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "eusart.h"

//#define TRA
#define REC

// CONFIG1
#pragma config FOSC = HS        // Oscilador externo HS, cristal de 8 MHz
#pragma config WDTE = OFF       // Watchdog Timer apagado
#pragma config PWRTE = OFF      // Power-up Timer apagado
#pragma config MCLRE = ON       // MCLR habilitado
#pragma config CP = OFF         // Code Protection apagado
#pragma config CPD = OFF        // Data Code Protection apagado
#pragma config BOREN = ON       // Brown-out Reset habilitado
#pragma config IESO = OFF       // Internal/External Switchover apagado
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor apagado
#pragma config LVP = OFF        // Low Voltage Programming apagado

// CONFIG2
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#ifdef TRA
#define BUTTON PORTBbits.RB0

void GPIO_Init(void)
{
    /*
     * Desactivar entradas analógicas.
     * RB0 también puede funcionar como AN12, por eso es importante ANSELH = 0.
     */
    ANSEL = 0x00;
    ANSELH = 0x00;

    /*
     * RB0 como entrada para botón.
     */
    TRISBbits.TRISB0 = 1;

    /*
     * Pull-up interno en RB0.
     */
    OPTION_REGbits.nRBPU = 0;   // Habilita pull-ups globales de PORTB
    WPUBbits.WPUB0 = 1;         // Habilita pull-up individual en RB0
}

void main(void)
{
    uint8_t lastButtonState;
    uint8_t currentButtonState;

    GPIO_Init();
    EUSART_Init();

    lastButtonState = BUTTON;

    while (1)
    {
        currentButtonState = BUTTON;

        if (currentButtonState != lastButtonState)
        {
            __delay_ms(25); // Antirrebote

            currentButtonState = BUTTON;

            if (currentButtonState != lastButtonState)
            {
                lastButtonState = currentButtonState;

                if (currentButtonState == 0)
                {
                    /*
                     * Botón presionado.
                     * Manda comando para encender LED.
                     */
                    EUSART_WriteByte(UART_LED_ON);
                }
                else
                {
                    /*
                     * Botón soltado.
                     * Manda comando para apagar LED.
                     */
                    EUSART_WriteByte(UART_LED_OFF);
                }
            }
        }
    }
}

#endif

#ifdef REC
#define LED PORTDbits.RD0

void GPIO_Init(void)
{
    /*
     * Desactivar entradas analógicas.
     */
    ANSEL = 0x00;
    ANSELH = 0x00;

    /*
     * RD0 como salida para LED.
     */
    TRISDbits.TRISD0 = 0;
    LED = 0;
}

void main(void)
{
    uint8_t receivedData;

    GPIO_Init();
    EUSART_Init();

    while (1)
    {
        if (EUSART_ReadByte(&receivedData))
        {
            if (receivedData == UART_LED_ON)
            {
                LED = 1;
            }
            else if (receivedData == UART_LED_OFF)
            {
                LED = 0;
            }
        }
    }
}
#endif