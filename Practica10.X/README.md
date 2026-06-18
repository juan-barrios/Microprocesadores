<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">INTERRUPCIONES INTERNAS (TIMER1)</h1>
  <p style="color: #888; font-family: monospace;">Práctica #10</p>
</div>

## Objetivo Principal
Diseñar e implementar un sistema concurrente utilizando las interrupciones por hardware del microcontrolador PIC16F887, específicamente mediante el módulo **Timer1**. El proyecto requiere el análisis de la hoja de datos (datasheet) para la correcta configuración de los registros y periféricos del microcontrolador, con el fin de crear una base de tiempo exacta para un reloj de 12 horas (eliminando el uso de retardos bloqueantes). Adicionalmente, se busca integrar la lectura del convertidor analógico a digital (ADC) para mostrar simultáneamente el tiempo y el voltaje en una pantalla LCD.

---

## Materiales Utilizados
* Display LCD de 16x2
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V
* 1 x Botón (Pulsador)
* 1 x Potenciómetro de 10kΩ (Configurado como entrada analógica en el pin RB0)
* 1 x Potenciómetro de 1kΩ (Para controlar el contraste/brillo de la pantalla LCD)

---

## Resultados

La práctica se desarrolló en dos fases, integrando el aprendizaje de nuevos periféricos y la lectura analógica.

### Actividad de Clase: Reloj con Timer1 y Manejo de Registros
Se configuró el módulo Timer1 del PIC16F887. Para lograr esto, fue indispensable consultar la documentación oficial del fabricante para comprender el funcionamiento de sus registros específicos y la habilitación de interrupciones de periféricos (PEIE). Con esta configuración se programó un reloj en formato de 12 horas, cuya actualización de tiempo ocurre en segundo plano mediante interrupciones, sustituyendo completamente la necesidad de utilizar comandos como `__delay_ms()`.

### Actividad 1: Integración de Reloj y Lectura de Voltaje (ADC)
Se expandió la funcionalidad del reloj base añadiendo la lectura continua de un nivel de voltaje analógico a través del puerto RB0. El sistema final logra mostrar dos procesos simultáneos en el display LCD sin interferir en la precisión del tiempo:
* **Esquina superior izquierda:** Despliegue de la medición de voltaje obtenida por el ADC.
* **Esquina inferior derecha:** Despliegue del contador de reloj (12 horas) controlado por el Timer1.

A continuación, se presentan los espacios de evidencia correspondientes al funcionamiento del sistema:

| Simulación del Sistema | Armado Físico (Actividad 1) |
| :---: | :---: |
| <img width="500" alt="[Insertar imagen de simulación en Proteus aquí]" src="[Insertar enlace de imagen aquí]" /> | <img width="500" alt="[Insertar imagen del circuito físico en protoboard]" src="[Insertar enlace de imagen aquí]" /> |

| Funcionalidad Evaluada | Descripción del Comportamiento Visual | Evidencia de Funcionamiento |
| :--- | :--- | :---: |
| **Reloj de 12 Horas (Timer1)** | Conteo de tiempo preciso en la esquina inferior derecha, operando sin interrupciones visuales. | <img width="250" alt="[Insertar imagen del reloj]" src="[Insertar enlace aquí]" /> |
| **Lectura Analógica en RB0** | Voltaje variable reflejado en tiempo real en la esquina superior izquierda de la pantalla. | <img width="250" alt="[Insertar imagen de lectura de voltaje]" src="[Insertar enlace aquí]" /> |

---

## Conclusiones

Juan:

Esta práctica fue retadora, aunque no por temas de código o de implementaciones físicas que se requirieran, en cambio, la dificultad de esta práctica recae en la documentación. Aprender a cómo leer la documentación así como entender cómo se deben de emplear cada uno de los detalles para poder realizar desarrollos independientes a las actividades de clase.

Erick:

