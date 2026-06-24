<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">MODULACIÓN DE BRILLO (TIMER1 Y TIMER2)</h1>
  <p style="color: #888; font-family: monospace;">Práctica #11</p>
</div>

## Objetivo Principal
Implementar y comparar dos técnicas de modulación por ancho de pulsos (PWM) para el control de la intensidad luminosa de dos LEDs de manera independiente, utilizando el microcontrolador PIC16F887. Se busca dominar la generación de señales PWM por **Hardware** (empleando el módulo CCP y el Timer2) y la generación de señales PWM por **Software** (mediante interrupciones internas gestionadas por el Timer1), controlando el ciclo de trabajo de ambas señales a través de lecturas analógicas independientes.

---

## Materiales Utilizados
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V
* 1 x Botón (Pulsador)
* 2 x Potenciómetros de 10kΩ (Configurados como entradas analógicas en los pines RA0 y RA1)
* 2 x LEDs (Actuadores visuales para el control de brillo)
* Resistencias (Para limitación de corriente en LEDs y configuración del botón)

---

## Resultados

El desarrollo de la práctica permitió contrastar la eficiencia y metodología de dos enfoques diferentes para la generación de señales PWM dentro del mismo microcontrolador.

### Actividad de Clase: PWM por Hardware (Timer2)
Se configuró el módulo CCP (Capture/Compare/PWM) interno del PIC para generar una señal PWM controlada completamente por el hardware del microcontrolador, utilizando el **Timer2** como base de tiempo. El ciclo de trabajo (duty cycle) de esta señal, que determina el brillo del primer LED, se ajustó dinámicamente según la lectura analógica obtenida del potenciómetro conectado al pin RA0.

### Actividad 1: PWM Híbrido (Hardware + Software)
Se amplió el sistema de la actividad de clase integrando un segundo LED y un segundo potenciómetro (RA1). Para controlar este segundo LED, se desarrolló un PWM por **Software**, el cual genera la modulación encendiendo y apagando el puerto digital correspondiente mediante rutinas de interrupción controladas por el desbordamiento del **Timer1**. Como resultado, se obtuvo el control independiente de ambos LEDs: uno operando por el módulo nativo del PIC y el otro emulado mediante lógica de programación y temporizadores.

A continuación, se presentan las tablas de evidencia correspondientes al montaje y funcionamiento de los moduladores:

| Simulación del Sistema PWM | Armado Físico (Actividad 1) |
| :---: | :---: |
|<img width="1022" height="382" alt="image" src="https://github.com/user-attachments/assets/30ffea29-e7f8-49ce-9610-1fb9bd720568" />| <img width="3072" height="4096" alt="1782315317281" src="https://github.com/user-attachments/assets/7a32979f-486e-446a-bc42-4174f618cee3" />|

| Funcionalidad | Descripción del Comportamiento Visual | Evidencia de Funcionamiento |
| :--- | :--- | :---: |
| **Control de Brillo (Hardware RA0 / Software RA1)** | Demostración de la variación independiente y suave del brillo en ambos componentes: el LED 1 regulado por hardware (Timer2 y módulo CCP) y el LED 2 emulado por software a través de interrupciones de Timer1. |<img width="652" height="367" alt="VID_20260623_140831 (1)" src="https://github.com/user-attachments/assets/64c40358-8773-4d52-8c5b-7c89ae03c43b" />|

---

## Conclusiones

Juan:

Esta fue una actividad bastante entretenida, porque tuvimos que emplear conceptos de múltiples prácticas anteriores, como la lectura de datos de una entrada analógica, el Timer1, etc. Y, por lo mismo, estar buscando y recordando conceptos previos me sirvió para repasar los conocimientos que ya traíamos de otras prácticas.

Erick:

Con este proyecto logré integrar con éxito conceptos de conversión analógica, temporizadores e interrupciones dinámicas para controlar potencia mediante el ancho de pulso. Lo más interesante fue programar dos canales independientes que tradujeran el voltaje de los potenciómetros para encender los leds
