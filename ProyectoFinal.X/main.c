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


/*
 * Objetivo: Crear un simulador de un elevador
 * 
 * Funcionalidades:
 * - Desplazarse entre pisos --> Debe de encender el led que 'corresponde' a cada piso
 *   - Se muestra en la pantalla LCD el piso en el que esta actualmente
 *   - Se muestra la direccion (arriba o abajo), hacia donde se dirige
 *   - Se tiene orden de prioridades, los pisos de arriba primero
 *   - Se usara el teclado matricial para poder seleccionar pisos
 * - Pantalla LCD
 *   - Muestra informacion del estado actual: Piso, direccion y estado actual (subiendo, abriendo puertas, cerrando puertas, etc)
 * - Estados del elevador
 *   - Debe de ser capaz de manejar distintos estados
 *   - Cada uno tiene una duracion distinta, y va ligada al Timer1
 * 
 * Configuracion fisica:
 * LCD 16x2  -> PORTC
 * Teclado   -> PORTB
 * LEDs 1-6  -> PORTD
 * Timer1    -> genera el tiempo de subida/bajada y el tiempo para abrir/cerrar las puertas
 */


/* Configuraciones para los perifericos externos:
 * LEDs para el cambio de pisos:
 * Piso 1 -> RD0
 * Piso 2 -> RD1
 * Piso 3 -> RD2
 * Piso 4 -> RD3
 * Piso 5 -> RD4
 * Piso 6 -> RD5
 * 
 * Teclado matricial:
 * Filas     -> RB0, RB1, RB2, RB3
 * Columnas  -> RB4, RB5, RB6, RB7
 */

// Definiciones para variables
#define NUM_FLOORS 6

// Timer1 con Fosc = 8 MHz
// Fosc/4 = 2 MHz
// Tcy = 0.5 us
// Prescaler 1:8 -> Timer1 incrementa cada 4 us
// 100 ms / 4 us = 25000 cuentas
// Preload = 65536 - 25000 = 40536 = 0x9E58
#define TMR1_PRELOAD   40536u
#define TMR1_PRELOAD_H ((unsigned char)(TMR1_PRELOAD >> 8))
#define TMR1_PRELOAD_L ((unsigned char)(TMR1_PRELOAD & 0x00FF))

// Duraciones usando ticks de 100 ms
#define FLOOR_TRAVEL_TICKS    10   // 1.0 s entre pisos
#define DOOR_OPENING_TICKS     5   // 0.5 s abriendo
#define DOOR_OPEN_TICKS       20   // 2.0 s abierta
#define DOOR_CLOSING_TICKS     5   // 0.5 s cerrando

// Caracteres especiales
char upArrow[8] = {
  0x04, // 00100
  0x0E, // 01110
  0x1F, // 11111
  0x04, // 00100
  0x04, // 00100
  0x04, // 00100
  0x04, // 00100
  0x00  // 00000
};

char downArrow[8] = {
  0x04, // 00100
  0x04, // 00100
  0x04, // 00100
  0x04, // 00100
  0x1F, // 11111
  0x0E, // 01110
  0x04, // 00100
  0x00  // 00000
};

// Declaraciones de los eventos y transiciones
typedef enum { // Estados disponibles
    STATE_IDLE,
    STATE_REQUEST_RECEIVED,
    STATE_MOVING_UP,
    STATE_MOVING_DOWN,
    STATE_DOOR_OPENING,
    STATE_DOOR_OPEN,
    STATE_DOOR_CLOSING
} State_t;

typedef enum { // Eventos que pueden ocurrir en el elevador
    EVENT_NONE,
    EVENT_FLOOR_REQUEST,
    EVENT_TIMER_TICK
} Event_t;


// Variables de control
State_t currentState = STATE_IDLE;

unsigned char currentFloor = 1;
unsigned char targetFloor = 1;
unsigned char requestedFloor = 1;

// Índices 1 a 6. La posición 0 no se usa --> Para los pisos
unsigned char floorRequests[NUM_FLOORS + 1] = {0};

unsigned char stateTickCounter = 0;
unsigned char lcdNeedsUpdate = 1;

volatile unsigned char timerTicksPending = 0;

LCD screen = {&PORTC, 2, 3, 4, 5, 6, 7};

// Teclado 4x4
const char keypadMap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Prototipos para las funciones
void setup(void);
void Timer1_Init(void);

char Keypad_ReadRaw(void);
char Keypad_GetKey(void);

Event_t Event_Get(void);

void AddFloorRequest(unsigned char floor);
unsigned char HasAnyRequest(void);
unsigned char SelectNextFloor(void);

void StateMachine_Goto(State_t nextState);
void StateMachine_StartNextRequest(void);
void StateMachine_Update(Event_t event);

void Outputs_Update(void);

// Funcion que genera los cambios dependiendo del estado
void StateMachine_Update(Event_t event)
{
    if(event == EVENT_TIMER_TICK)
    {
        stateTickCounter++;
    }

    switch(currentState)
    {
        case STATE_IDLE:
            if(event == EVENT_FLOOR_REQUEST)
            {
                StateMachine_Goto(STATE_REQUEST_RECEIVED);
                StateMachine_StartNextRequest();
            }
            break;

        case STATE_REQUEST_RECEIVED:
            StateMachine_StartNextRequest();
            break;

        case STATE_MOVING_UP:
            if(event == EVENT_TIMER_TICK)
            {
                if(stateTickCounter >= FLOOR_TRAVEL_TICKS)
                {
                    stateTickCounter = 0;
                    currentFloor++;
                    lcdNeedsUpdate = 1;

                    if(currentFloor >= targetFloor || floorRequests[currentFloor])
                    {
                        floorRequests[currentFloor] = 0;
                        StateMachine_Goto(STATE_DOOR_OPENING);
                    }
                }
            }
            break;

        case STATE_MOVING_DOWN:
            if(event == EVENT_TIMER_TICK)
            {
                if(stateTickCounter >= FLOOR_TRAVEL_TICKS)
                {
                    stateTickCounter = 0;
                    currentFloor--;
                    lcdNeedsUpdate = 1;

                    if(currentFloor <= targetFloor || floorRequests[currentFloor])
                    {
                        floorRequests[currentFloor] = 0;
                        StateMachine_Goto(STATE_DOOR_OPENING);
                    }
                }
            }
            break;

        case STATE_DOOR_OPENING:
            if(event == EVENT_TIMER_TICK)
            {
                if(stateTickCounter >= DOOR_OPENING_TICKS)
                {
                    StateMachine_Goto(STATE_DOOR_OPEN);
                }
            }
            break;

        case STATE_DOOR_OPEN:
            if(event == EVENT_TIMER_TICK)
            {
                if(stateTickCounter >= DOOR_OPEN_TICKS)
                {
                    StateMachine_Goto(STATE_DOOR_CLOSING);
                }
            }
            break;

        case STATE_DOOR_CLOSING:
            if(event == EVENT_TIMER_TICK)
            {
                if(stateTickCounter >= DOOR_CLOSING_TICKS)
                {
                    if(HasAnyRequest())
                    {
                        StateMachine_Goto(STATE_REQUEST_RECEIVED);
                        StateMachine_StartNextRequest();
                    }
                    else
                    {
                        StateMachine_Goto(STATE_IDLE);
                    }
                }
            }
            break;

        default:
            StateMachine_Goto(STATE_IDLE);
            break;
    }
}

void setup(void)
{
    // Desactivar entradas analógicas
    ANSEL = 0x00;
    ANSELH = 0x00;

    // Desactivar comparadores
    CM1CON0 = 0x00;
    CM2CON0 = 0x00;

    // LCD en PORTC desde RC2 hasta RC7
    PORTC = 0x00;
    TRISC = 0x00;

    // Teclado matricial en PORTB
    // RB0-RB3 = filas como salidas
    // RB4-RB7 = columnas como entradas
    PORTB = 0xFF;
    TRISB = 0b11110000;

    // Pull-ups internos para columnas RB4-RB7
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b11110000;

    // LEDs de los 6 pisos en PORTD
    // RD0 = piso 1
    // RD1 = piso 2
    // RD2 = piso 3
    // RD3 = piso 4
    // RD4 = piso 5
    // RD5 = piso 6
    PORTD = 0x00;
    TRISD = 0x00;

    // Inicializar LCD usando tu estructura
    LCD_Init(screen);
    LCD_Clear();

    LCD_Custom_Char(0, upArrow);
    LCD_Custom_Char(1, downArrow);

    Timer1_Init();
}

void Timer1_Init(void)
{
    T1CONbits.TMR1ON = 0;

    // Timer1 usando reloj interno Fosc/4.
    // Con Fosc = 8 MHz:
    // Fosc/4 = 2 MHz
    // Tcy = 0.5 us
    T1CONbits.TMR1CS = 0;

    // Prescaler 1:8
    // Timer1 incrementa cada 0.5 us * 8 = 4 us
    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1;

    T1CONbits.T1OSCEN = 0;

    // Precarga para interrupción cada 100 ms
    TMR1H = TMR1_PRELOAD_H;
    TMR1L = TMR1_PRELOAD_L;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    T1CONbits.TMR1ON = 1;
}

char Keypad_ReadRaw(void)
{
    unsigned char row;
    unsigned char col;
    unsigned char cols;

    const unsigned char rowPattern[4] = {
        0b00001110, // RB0 en 0
        0b00001101, // RB1 en 0
        0b00001011, // RB2 en 0
        0b00000111  // RB3 en 0
    };

    PORTB = 0xFF;

    for(row = 0; row < 4; row++)
    {
        PORTB = 0xF0 | rowPattern[row];

        __delay_us(50);

        cols = (PORTB >> 4) & 0x0F;

        for(col = 0; col < 4; col++)
        {
            if((cols & (1u << col)) == 0)
            {
                PORTB = 0xFF;
                return keypadMap[row][col];
            }
        }
    }

    PORTB = 0xFF;
    return '\0';
}

char Keypad_GetKey(void)
{
    static char lastKey = '\0';

    char rawKey = Keypad_ReadRaw();

    if(rawKey != '\0' && lastKey == '\0')
    {
        lastKey = rawKey;
        return rawKey;
    }

    if(rawKey == '\0')
    {
        lastKey = '\0';
    }

    return '\0';
}

Event_t Event_Get(void)
{
    char key = Keypad_GetKey();

    if(key >= '1' && key <= '6')
    {
        AddFloorRequest((unsigned char)(key - '0'));
        return EVENT_FLOOR_REQUEST;
    }

    if(timerTicksPending > 0)
    {
        timerTicksPending--;
        return EVENT_TIMER_TICK;
    }

    return EVENT_NONE;
}

void AddFloorRequest(unsigned char floor)
{
    if(floor >= 1 && floor <= NUM_FLOORS)
    {
        requestedFloor = floor;
        floorRequests[floor] = 1;
        lcdNeedsUpdate = 1;
    }
}

unsigned char HasAnyRequest(void)
{
    unsigned char floor;

    for(floor = 1; floor <= NUM_FLOORS; floor++)
    {
        if(floorRequests[floor])
        {
            return 1;
        }
    }

    return 0;
}

unsigned char SelectNextFloor(void)
{
    unsigned char floor;

    if(floorRequests[currentFloor])
    {
        return currentFloor;
    }

    // Prioridad: pisos superiores primero
    for(floor = currentFloor + 1; floor <= NUM_FLOORS; floor++)
    {
        if(floorRequests[floor])
        {
            return floor;
        }
    }

    // Después, pisos inferiores
    for(floor = currentFloor; floor > 1; floor--)
    {
        if(floorRequests[floor - 1])
        {
            return floor - 1;
        }
    }

    return currentFloor;
}

void StateMachine_Goto(State_t nextState)
{
    currentState = nextState;
    stateTickCounter = 0;
    lcdNeedsUpdate = 1;
}

void StateMachine_StartNextRequest(void)
{
    if(!HasAnyRequest())
    {
        StateMachine_Goto(STATE_IDLE);
        return;
    }

    targetFloor = SelectNextFloor();

    if(targetFloor > currentFloor)
    {
        StateMachine_Goto(STATE_MOVING_UP);
    }
    else if(targetFloor < currentFloor)
    {
        StateMachine_Goto(STATE_MOVING_DOWN);
    }
    else
    {
        floorRequests[currentFloor] = 0;
        StateMachine_Goto(STATE_DOOR_OPENING);
    }
}

// Funcion para generar los cambios dependiendo del estado
void Outputs_Update(void)
{
    unsigned char ledMask = 0x00;

    // Encender LED del piso actual en RD0-RD5
    if(currentFloor >= 1 && currentFloor <= NUM_FLOORS)
    {
        ledMask = (unsigned char)(1u << (currentFloor - 1));
    }

    PORTD = ledMask;

    // No actualizar LCD en cada vuelta del while(1)
    if(!lcdNeedsUpdate)
    {
        return;
    }

    lcdNeedsUpdate = 0;

    LCD_Clear();

    // Primera línea
    LCD_Set_Cursor(0, 1);
    LCD_putrs("Piso:");
    LCD_putc(currentFloor + '0');

    LCD_putrs(" Obj:");

    if(currentState == STATE_IDLE && !HasAnyRequest())
    {
        LCD_putc('-');
    }
    else
    {
        LCD_putc(targetFloor + '0');
    }

    // Segunda línea
    LCD_Set_Cursor(1, 1);

    switch(currentState)
    {
        case STATE_IDLE:
            LCD_putrs("En espera");
            break;

        case STATE_REQUEST_RECEIVED:
            LCD_putrs("Procesando");
            break;

        case STATE_MOVING_UP:
            LCD_putrs("Subiendo");
            LCD_putc(0);
            break;

        case STATE_MOVING_DOWN:
            LCD_putrs("Bajando");
            LCD_putc(1);
            break;

        case STATE_DOOR_OPENING:
            LCD_putrs("Abriendo");
            break;

        case STATE_DOOR_OPEN:
            LCD_putrs("Puerta abierta");
            break;

        case STATE_DOOR_CLOSING:
            LCD_putrs("Cerrando");
            break;

        default:
            LCD_putrs("Error");
            break;
    }
}

void main(void)
{
    setup();

    while(1)
    {
        Event_t event = Event_Get();

        if(event != EVENT_NONE) {
            StateMachine_Update(event);
        }

        Outputs_Update();
    }
}

void __interrupt() ISR(void)
{
    if(PIR1bits.TMR1IF && PIE1bits.TMR1IE)
    {
        TMR1H = TMR1_PRELOAD_H;
        TMR1L = TMR1_PRELOAD_L;

        PIR1bits.TMR1IF = 0;

        if(timerTicksPending < 250)
        {
            timerTicksPending++;
        }
    }
}


