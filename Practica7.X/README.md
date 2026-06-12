<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">USO DE PUERTOS ANALÓGICOS</h1>
  <p style="color: #888; font-family: monospace;">Práctica #7</p>
</div>

## Objetivo Principal
Comprender e implementar el uso del convertidor analógico a digital (ADC) del microcontrolador PIC16F887. Se busca medir el voltaje de entrada analógico mediante el puerto RA0, procesar esta lectura y mostrar la información procesada (voltaje, porcentaje y valor ADC) en un display LCD, implementando interrupciones externas para navegar entre distintas pantallas de visualización.

---

## Materiales Utilizados
* Display LCD de 18x2
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V
* 2 x Botones 
* 1 x Potenciómetro de 10kΩ
* 1 x Potenciómetro de 1kΩ

---

## Resultados

Durante esta práctica se llevaron a cabo dos actividades enfocadas en la lectura y procesamiento de señales analógicas.

### Actividad de Clase: Lectura Básica (Simulación)
Se configuró el puerto analógico RA0 como entrada para leer la variación de voltaje generada por un potenciómetro. Mediante el entorno de simulación, se verificó la correcta lectura del voltaje de entrada y su visualización en tiempo real en la pantalla LCD.

### Actividad 1: Interfaz de Multímetro con Interrupciones
Se desarrolló el circuito físico donde se lee el voltaje variable controlado por el potenciómetro externo en el pin RA0. Se implementó un sistema de menús en el display LCD controlado mediante un botón externo configurado por **interrupciones**. El botón permite ciclar entre tres pantallas de información:

1. **Pantalla 1:** Voltaje de entrada actual (0V - 5V).
2. **Pantalla 2:** Porcentaje correspondiente al voltaje (0% - 100%, respecto a 5V).
3. **Pantalla 3:** Valor crudo del ADC (0 - 1023, donde 1023 corresponde a 5V).

A continuación se presentan las evidencias visuales y los diagramas de funcionamiento de las actividades realizadas:

| Simulación (Actividad de Clase) | Armado Físico (Actividad 1) |
| :---: | :---: |
| <img width="500" alt="[Insertar imagen de simulación aquí]" src="[Insertar enlace de imagen aquí]" /> | <img width="500" alt="[Insertar imagen del armado aquí]" src="[Insertar enlace de imagen aquí]" /> |

| Pantalla LCD | Descripción del Estado Visual | Evidencia de Funcionamiento |
| :--- | :--- | :---: |
| **Pantalla 1 (Voltaje)** | Muestra el voltaje exacto calculado en base a la entrada analógica. | <img width="250" alt="[Insertar imagen Pantalla 1]" src="[Insertar enlace aquí]" /> |
| **Pantalla 2 (Porcentaje)** | Muestra la representación porcentual del voltaje máximo de 5V. | <img width="250" alt="[Insertar imagen Pantalla 2]" src="[Insertar enlace aquí]" /> |
| **Pantalla 3 (ADC)** | Muestra el valor numérico en binario/decimal (0-1023) detectado por el convertidor. | <img width="250" alt="[Insertar imagen Pantalla 3]" src="[Insertar enlace aquí]" /> |

---

## Conclusiones

Juan:

Durante esta práctica pude entender de mucho mejor forma cómo emplear los displays de LCD para mostrar información en pantalla. Mejorando significativamente a cómo se realizaron las cosas durante la práctica #6, corrigiendo errores y adaptando el código para corregir los errores que se tenían.


Erick:

