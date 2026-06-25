#include "eusart.h"

void EUSART_Init(void)
{
    /*
     * Pines UART del PIC16F887:
     * RC6 = TX
     * RC7 = RX
     */
    TRISCbits.TRISC6 = 0;   // TX como salida
    TRISCbits.TRISC7 = 1;   // RX como entrada

    /*
     * Limpiar registros principales del módulo EUSART
     */
    TXSTA = 0x00;
    RCSTA = 0x00;
    BAUDCTL = 0x00;

    /*
     * Configuración UART:
     * FOSC = 8 MHz
     * Baud rate = 9600
     * BRG16 = 1
     * BRGH = 1
     *
     * SPBRG = 207 = 0x00CF
     */
    BAUDCTLbits.BRG16 = 1;  // Baud Rate Generator de 16 bits

    SPBRGH = 0x00;
    SPBRG  = 0xCF;

    /*
     * Modo asíncrono de alta velocidad
     */
    TXSTAbits.SYNC = 0;     // 0 = modo asíncrono
    TXSTAbits.BRGH = 1;     // 1 = alta velocidad

    /*
     * Habilitar puerto serial, transmisión y recepción
     */
    RCSTAbits.SPEN = 1;     // Habilita EUSART y usa RC6/RC7
    TXSTAbits.TXEN = 1;     // Habilita transmisión
    RCSTAbits.CREN = 1;     // Habilita recepción continua

    /*
     * No usamos interrupciones en esta versión
     */
    PIE1bits.RCIE = 0;
    PIE1bits.TXIE = 0;

    EUSART_FlushRx();
}

void EUSART_WriteByte(uint8_t data)
{
    while (!PIR1bits.TXIF); // Espera a que TXREG esté vacío
    TXREG = data;
}

void EUSART_WriteText(const char *text)
{
    while (*text != '\0')
    {
        EUSART_WriteByte((uint8_t)*text);
        text++;
    }
}

bool EUSART_DataReady(void)
{
    return PIR1bits.RCIF;
}

uint8_t EUSART_ReadByteBlocking(void)
{
    uint8_t data;

    while (!PIR1bits.RCIF);

    EUSART_HandleErrors();

    if (RCSTAbits.FERR)
    {
        data = RCREG;
        return 0;
    }

    data = RCREG;
    return data;
}

bool EUSART_ReadByte(uint8_t *data)
{
    if (!PIR1bits.RCIF)
    {
        return false;
    }

    EUSART_HandleErrors();

    if (RCSTAbits.FERR)
    {
        volatile uint8_t dummy = RCREG;
        (void)dummy;
        return false;
    }

    *data = RCREG;
    return true;
}

void EUSART_HandleErrors(void)
{
    /*
     * OERR = Overrun Error
     * Si ocurre, se debe reiniciar la recepción continua.
     */
    if (RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0;
        NOP();
        RCSTAbits.CREN = 1;
    }
}

void EUSART_FlushRx(void)
{
    while (PIR1bits.RCIF)
    {
        volatile uint8_t dummy = RCREG;
        (void)dummy;
    }
}