#include <xc.h>         // Biblioteca principal del compilador XC8

//#define PROBA // Multiplexacion con contador de 4 digitos
//#define PROBB // Interrupciones
#define ACT // Contador del 0 al 9999
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


#ifdef PROBA
unsigned char conteo[10] = {0x3F, 0x6,0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x67};

void main(void){
    TRISD = 0; // Salida
    TRISC = 0;
    
    int num = 0;
    
    while(1){
        int dec = (num/10)%10; // Decenas
        int uni = num%10; // Unidades
        int cen = (num/100)%10; // Centenas
        int mill = (num/1000)%10; // Millares
        
        for(int i = 0; i < 50; i++){ // Llega hasta 1/5 de segundo
            // Mostrar las millares
            PORTC = 0b11110111;
            PORTD = conteo[mill];
             __delay_ms(1);
            
            // Mostrar las centenas
            PORTC = 0b11111011;
            PORTD = conteo[cen];
             __delay_ms(1);
            
            // Mostrar las decenas
            PORTC = 0b11111101; // Esto manda un 0 a RC1
            PORTD = conteo[dec]; // Para que puerto D muestre las decenas
            
            __delay_ms(1);
            
            // Mostrar las unidades
            PORTC = 0b11111110; // Esto manda un 0 a RC0
            PORTD = conteo[uni]; // Para que puerto D muestre las decenas
            
            __delay_ms(1);
        }
        
        //num = (num+1)%100; // Para que se mantenga entre 0 - 99
        num = (num+1)%10000;
    }
}


#endif

#ifdef PROBB
#define LED PORTCbits.RC0
unsigned char conteo[10] = {0xFC, 0x60,0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};

void blink_led(){
    for(int i = 1; i < 4; i++){
        LED = 1;
        __delay_ms(500);
        
        LED = 0;
        __delay_ms(500);
    }
}


void main(void){
    ANSEL = 0;
    ANSELH = 0;
    
    OPTION_REG = OPTION_REG & 0b01111111;
    
    TRISC = 0;
    TRISD = 0;
    TRISB = 0xFF;
    
    PORTC = 0;
    PORTD = 0;
    
    // Para activar las interrupciones globales
    GIE = 1; // Para que __interrupt este activa todo el tiempo
    INTE = 1; // RB0 ya no es entrada digital, ahora es de interrupcion
    INTEDG = 0; // Para flanco de bajadad (por las resistencias de pull up)

    unsigned char count = 0;
    while(1){
        PORTD = conteo[count];
        
        __delay_ms(500);
        
        count = (count+1)%10; // Del 0 al 9
    }
}   

void __interrupt() ISR(void){
    if(INTF){ // flag que se activa cuando hay interrupcion externa (ya viene dentro del PIC)
        GIE = 0; // Para que la interrupcion no interrupma a la interrupcion
        blink_led(); // LED blinkea 4 veces
        GIE = 1; // Se vuelven a habilitar las interrupciones
        INTF = 0; // Para salir de la interrupcion
    }
}
#endif

/*
 Contador del 0 al 9999
 * Se usa 1 boton:
 *  - Si se presiona 1 vez, cuenta hacia atras
 *  - Si se vuelve a presionar, cuenta hacia adelante
 */
#ifdef ACT
unsigned char conteo[10] = {0x3F, 0x6,0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x67};
int direction = 1; // Hacia adelante

int reverse_direction(int dir){
    if(dir == 1){
        return 0;
    }
    return 1;
}

void main(void){
    ANSEL = 0;
    ANSELH = 0;
    
    OPTION_REG = OPTION_REG & 0b01111111;
    
    TRISC = 0;
    TRISD = 0;
    TRISB = 0xFF;
    
    PORTC = 0;
    PORTD = 0;
    
    // Para activar las interrupciones globales
    GIE = 1; // Para que __interrupt este activa todo el tiempo
    INTE = 1; // RB0 ya no es entrada digital, ahora es de interrupcion
    INTEDG = 0; // Para flanco de bajadad (por las resistencias de pull up)
    
    int num = 0;
    
    while(1){
        int dec = (num/10)%10; // Decenas
        int uni = num%10; // Unidades
        int cen = (num/100)%10; // Centenas
        int mill = (num/1000)%10; // Millares
        
        for(int i = 0; i < 6; i++){ // Llega hasta 1/5 de segundo
            // Mostrar las millares
            PORTC = 0b11110111;
            PORTD = conteo[mill];
             __delay_ms(1);
            
            // Mostrar las centenas
            PORTC = 0b11111011;
            PORTD = conteo[cen];
             __delay_ms(1);
            
            // Mostrar las decenas
            PORTC = 0b11111101; // Esto manda un 0 a RC1
            PORTD = conteo[dec]; // Para que puerto D muestre las decenas
            
            __delay_ms(1);
            
            // Mostrar las unidades
            PORTC = 0b11111110; // Esto manda un 0 a RC0
            PORTD = conteo[uni]; // Para que puerto D muestre las decenas
            
            __delay_ms(1);
        }
        
        
        if(direction == 1){
            num = (num+1)%10000;
        }else{
            if(num > -1){
                num = (num-1)%10000;
            }else{
                num = 9999;
            }
        }        
    }
}

void __interrupt() ISR(void){
    if(INTF){ // flag que se activa cuando hay interrupcion externa (ya viene dentro del PIC)
        GIE = 0; // Para que la interrupcion no interrupma a la interrupcion
        direction = reverse_direction(direction); 
        GIE = 1; // Se vuelven a habilitar las interrupciones
        INTF = 0; // Para salir de la interrupcion
    }
}

#endif

