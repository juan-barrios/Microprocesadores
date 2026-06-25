#ifndef EUSART_H
#define EUSART_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define _XTAL_FREQ 8000000UL
#define EUSART_BAUD 9600UL

#define UART_LED_ON   '1'
#define UART_LED_OFF  '0'

void EUSART_Init(void);

void EUSART_WriteByte(uint8_t data);
void EUSART_WriteText(const char *text);

bool EUSART_DataReady(void);
uint8_t EUSART_ReadByteBlocking(void);
bool EUSART_ReadByte(uint8_t *data);

void EUSART_HandleErrors(void);
void EUSART_FlushRx(void);

#endif