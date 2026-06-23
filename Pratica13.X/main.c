#include <xc.h>
//#define ACT1
#define ACT2
#pragma config FOSC = XT        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = ON       
#pragma config CP = OFF         
#pragma config CPD = OFF        
#pragma config BOREN = ON       
#pragma config IESO = OFF       
#pragma config FCMEN = OFF      
#pragma config LVP = OFF        

#define _XTAL_FREQ 8000000   
#ifdef ACT1
void PWM_Init(void) {
    TRISCbits.TRISC2 = 0;  // RC2 configurado como salida
    
    PR2 = 249;             
    CCP1CON = 0x0C;        
    T2CON = 0x05;          
}

void PWM_Set_Duty(unsigned int duty) {
    if(duty > 1023) duty = 1023;
    CCPR1L = (unsigned char)(duty >> 2);            
    CCP1CON = (unsigned char)((CCP1CON & 0xCF) | ((duty & 0x03) << 4)); 
}

void main(void) {
    PWM_Init();
    
    while(1) {
        // Acelerar gradualmente
        for(unsigned int velocidad = 0; velocidad <= 1023; velocidad += 100) {
            PWM_Set_Duty(velocidad);
            __delay_ms(400);
        }
        __delay_ms(1000); 
        
        // Desacelerar gradualmente
        for(unsigned int velocidad = 1023; velocidad > 0; velocidad -= 100) {
            PWM_Set_Duty(velocidad);
            __delay_ms(400);
            if(velocidad < 100) break; 
        }
        
        PWM_Set_Duty(0);  
        __delay_ms(1000); 
    }
}
#endif

#ifdef ACT2
void PWM_Init(void) {
    TRISCbits.TRISC2 = 0;  // RC2 configurado como salida (Controla Velocidad)
    TRISDbits.TRISD0 = 0;  // RD0 configurado como salida (Controla Dirección)
    TRISDbits.TRISD1 = 0;  // RD1 configurado como salida (Controla Dirección)
    
    PR2 = 249;             
    CCP1CON = 0x0C;        
    T2CON = 0x05;          
}

void PWM_Set_Duty(unsigned int duty) {
    if(duty > 1023) {
        duty = 1023;
    }
    CCPR1L = (unsigned char)(duty >> 2);            
    CCP1CON = (unsigned char)((CCP1CON & 0xCF) | ((duty & 0x03) << 4)); 
}

void main(void) {
    // 1. CONFIGURACIÓN DEL PIN DEL BOTÓN (RB0)
    ANSELH = 0x00;            // Convierte todo el Puerto B a digital
    TRISBbits.TRISB0 = 1;     // Configura RB0 como entrada
    
    // 2. ACTIVACIÓN DE LA PULL-UP INTERNA
    OPTION_REGbits.nRBPU = 0; // Habilita las pull-ups globales del Puerto B (0 = ON)
    WPUBbits.WPUB0 = 1;       // Activa la pull-up específica del pin RB0
    
    // 3. INICIALIZACIÓN DEL PWM
    PWM_Init();
    
    int direccion = 0;        // Variable de estado: 0 = Derecha, 1 = Izquierda
    
    while(1) {
        // Leemos si el botón fue presionado (0 lógico gracias a la pull-up)
        if(PORTBbits.RB0 == 0) {
            __delay_ms(50);   // Filtro Anti-rebote por software
            
            if(PORTBbits.RB0 == 0) {
                direccion = !direccion; // Invierte el estado (de 0 a 1, o de 1 a 0)
                
                // Freno de seguridad obligatorio antes de invertir el voltaje
                PORTDbits.RD0 = 0;
                PORTDbits.RD1 = 0;
                PWM_Set_Duty(0);
                __delay_ms(500); 
                
                // Bucle de espera: el programa se pausa aquí hasta que sueltes el botón
                while(PORTBbits.RB0 == 0); 
            }
        }
        
        // Ejecución continua del giro según la variable de estado
        if(direccion == 0) {
            PORTDbits.RD0 = 1;
            PORTDbits.RD1 = 0;
            PWM_Set_Duty(700); // Velocidad al 70% aprox
        } else {
            PORTDbits.RD0 = 0;
            PORTDbits.RD1 = 1;
            PWM_Set_Duty(700); // Velocidad al 70% aprox
        }
    }
}
#endif 