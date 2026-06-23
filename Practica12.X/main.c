#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "lcd.h"

//#define ACT1
#define ACT2

//=============================================================================
// CONFIGURACI N DE BITS DE CONFIGURACI N (FUSES)
//=============================================================================

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

// Funciones para ambas actividades
// Funcion para configurar el teclado
void Teclado_Init(void)
{
    // Desactivar entradas analógicas --> La lectura es digital
    ANSEL = 0x00;
    ANSELH = 0x00;

    // RB0-RB3 como salidas: filas
    // RB4-RB7 como entradas: columnas
    TRISB = 0b11110000;

    // Inicialmente todas las filas en alto
    PORTB = 0xFF;

    // Activar pull-ups internos de PORTB --> Para que se detecten las caidas desde 1
    OPTION_REGbits.nRBPU = 0;   // Pull-ups globales habilitados
    WPUB = 0b11110000;          // Pull-ups en RB4-RB7
}

#ifdef ACT1
/*
 * Para leer un teclado matricial se deben de establecer valores base
 * Columnas --> 1 (siempre activas a menos de que se presionen)
 * Filas --> 1 (resultado de las columnas, bajan a 0)
 * 
 * Conexiones para el teclado (Todo queda en el puerto B):
 * Filas (quedan como salidas)
 * - R1 --> RB0
 * - R2 --> RB1
 * - R3 --> RB2
 * - R4 --> RB3
 * 
 * Columnas:
 * - C1 --> RB4
 * - C2 --> RB5
 * - C3 --> RB6
 * - C4 --> RB7
 */

// Mapeo del teclado matricial
const char map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};


// Funcion para procesar la tecla presionada
char Teclado_Read(){
    unsigned char row,col,cols;
    
    /*
     * Se debe de buscar fila por fila, hasta que se encuentre una columna conectada
     * Cuando se encuentre, se regresa el caracter y se para el sistema
    */
    
    for(row = 0; row < 4; row++){
        // Este comando lo que hace es ir poniendo en '0' una fila a la vez
        // Ponerlas en '0' es la manera de checar su valor
        PORTB = 0b11110000 | (0b00001111 & ~(1 << row));
        
        // Delay para que el teclado no lea valores erroneos
        __delay_us(50);
        
        // Lee y guarda los valores de las columas (Aqui se ve si alguna esta presionada)
        cols = (PORTB >> 4) & 0x0F;
        // El 0x0F es para eliminar los 4 ceros de la derecha y que queden las cuatro columnas solo
        
        for(col = 0; col < 4; col++){
           /*
            * Cols guarda los valores de las columnas actualmente
            * Lo que se hace es, basado en un corrimiento 'col'
            * Revisar si esa posicion en Cols es '0'
            * Si es 0 --> Esta presionada
            */
           if ((cols & (1 << col)) == 0)
            {
                __delay_ms(20); // Anti-rebote

                // Confirmar que sigue presionada
                cols = (PORTB >> 4) & 0x0F;
                if ((cols & (1 << col)) == 0)
                {
                    // Esperar a que se suelte
                    while ((((PORTB >> 4) & 0x0F) & (1 << col)) == 0);

                    __delay_ms(20); // Antirebote al soltar

                    PORTB = 0xFF;
                    return map[row][col];
                }
            } 
        }
    }
    
    PORTB = 0xFF;
    return '\0'; // Ninguna tecla presionada
}


void main(void)
{
    char tecla;
    unsigned char fila = 0;
    unsigned char columna = 0;

    Teclado_Init();
    
    LCD screen = {&PORTC, 2, 3, 4, 5, 6, 7};
    LCD_Init(screen); 

    LCD_Clear();
    LCD_Set_Cursor(fila, columna);

    while (1)
    {
        tecla = Teclado_Read();

        if (tecla != '\0')
        {
            // Solo escribir si todavía hay espacio en la LCD
            if (fila < 2)
            {
                LCD_Set_Cursor(fila, columna);
                LCD_putc(tecla);

                columna++;

                // Si llegamos al final de la primera línea
                if (columna >= 16)
                {
                    columna = 0;
                    fila++;
                }
            }
        }
    }
}

#endif


#ifdef ACT2
/*
 * Objetivo: Realizar una calculadora que sume, reste, multiplique o divida dos numeros
 * Se debe de poder realizar operaciones y mostrar hasta dos decimales de resultados
 */

const char map[4][4] = {
    {'1', '2', '3', '/'},
    {'4', '5', '6', '*'},
    {'7', '8', '9', '-'},
    {'C', '0', '=', '+'}
};

// Funcion para procesar la tecla presionada
char Teclado_Read(){
    unsigned char row,col,cols;
    
    /*
     * Se debe de buscar fila por fila, hasta que se encuentre una columna conectada
     * Cuando se encuentre, se regresa el caracter y se para el sistema
    */
    
    for(row = 0; row < 4; row++){
        // Este comando lo que hace es ir poniendo en '0' una fila a la vez
        // Ponerlas en '0' es la manera de checar su valor
        PORTB = 0b11110000 | (0b00001111 & ~(1 << row));
        
        // Delay para que el teclado no lea valores erroneos
        __delay_us(50);
        
        // Lee y guarda los valores de las columas (Aqui se ve si alguna esta presionada)
        cols = (PORTB >> 4) & 0x0F;
        // El 0x0F es para eliminar los 4 ceros de la derecha y que queden las cuatro columnas solo
        
        for(col = 0; col < 4; col++){
           /*
            * Cols guarda los valores de las columnas actualmente
            * Lo que se hace es, basado en un corrimiento 'col'
            * Revisar si esa posicion en Cols es '0'
            * Si es 0 --> Esta presionada
            */
           if ((cols & (1 << col)) == 0)
            {
                __delay_ms(20); // Anti-rebote

                // Confirmar que sigue presionada
                cols = (PORTB >> 4) & 0x0F;
                if ((cols & (1 << col)) == 0)
                {
                    // Esperar a que se suelte
                    while ((((PORTB >> 4) & 0x0F) & (1 << col)) == 0);

                    __delay_ms(20); // Antirebote al soltar

                    PORTB = 0xFF;
                    return map[row][col];
                }
            } 
        }
    }
    
    PORTB = 0xFF;
    return '\0'; // Ninguna tecla presionada
}



bool isDigitKey(char tecla) {
    return (tecla >= '0' && tecla <= '9');
}

bool isOperatorKey(char tecla) {
    return (tecla == '+' || tecla == '-' || tecla == '*' || tecla == '/');
}

long calc100(int first, int second, char op, bool *ok) {
    *ok = true;

    switch(op) {
        case '+':
            return ((long)first + second) * 100L;

        case '-':
            return ((long)first - second) * 100L;

        case '*':
            return ((long)first * second) * 100L;

        case '/':
            if(second == 0) {
                *ok = false;
                return 0;
            }
            return ((long)first * 100L) / second;

        default:
            *ok = false;
            return 0;
    }
}

void LCD_PrintLong(long num) {
    char digits[11];
    unsigned char i = 0;

    if(num == 0) {
        LCD_putc('0');
        return;
    }

    while(num > 0 && i < 10) {
        digits[i++] = (num % 10) + '0';
        num /= 10;
    }

    while(i > 0) {
        LCD_putc(digits[--i]);
    }
}

void LCD_PrintResult100(long result100) {
    long ent;
    unsigned char dec;

    if(result100 < 0) {
        LCD_putc('-');
        result100 = -result100;
    }

    ent = result100 / 100;
    dec = result100 % 100;

    LCD_PrintLong(ent);
    LCD_putc('.');
    LCD_putc((dec / 10) + '0');
    LCD_putc((dec % 10) + '0');
}

void main(void)
{
    char tecla;
    int firstNum = -1;
    int secondNum = -1;
    char op = '\0';
    unsigned char digit;
    long result100;
    bool ok;

    Teclado_Init();

    LCD screen = {&PORTC, 2, 3, 4, 5, 6, 7};
    LCD_Init(screen);

    LCD_Clear();

    while (1)
    {
        tecla = Teclado_Read();

        if(tecla == '\0') {
            continue;
        }

        if(tecla == 'C') {
            firstNum = -1;
            secondNum = -1;
            op = '\0';
            LCD_Clear();
        }

        else if(isDigitKey(tecla)) {
            digit = tecla - '0';

            if(op == '\0') {
                if(firstNum == -1) {
                    firstNum = 0;
                }

                firstNum = firstNum * 10 + digit;
            }
            else {
                if(secondNum == -1) {
                    secondNum = 0;
                }

                secondNum = secondNum * 10 + digit;
            }

            LCD_putc(tecla);
        }

        else if(isOperatorKey(tecla)) {
            if(firstNum != -1 && op == '\0') {
                op = tecla;
                LCD_putc(tecla);
            }
        }

        else if(tecla == '=') {
            if(firstNum != -1 && secondNum != -1 && op != '\0') {
                LCD_putc('=');

                result100 = calc100(firstNum, secondNum, op, &ok);

                LCD_Clear();

                if(ok) {
                    LCD_PrintResult100(result100);
                }
                else {
                    LCD_putrs("Error div 0");
                }

                firstNum = -1;
                secondNum = -1;
                op = '\0';
            }
        }
    }
}
#endif