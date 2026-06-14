<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">MÚLTIPLES ENTRADAS ANALÓGICAS</h1>
  <p style="color: #888; font-family: monospace;">Práctica #8</p>
</div>

## Objetivo Principal
Diseñar e implementar un sistema de adquisición de datos para múltiples canales utilizando el convertidor analógico a digital (ADC) del microcontrolador PIC16F887. Se busca medir dos señales de voltaje de manera independiente (pines RA0 y RA1), y desarrollar una interfaz interactiva en un display LCD mediante el uso de interrupciones externas, permitiendo al usuario alternar tanto la fuente de lectura como el formato de visualización (voltaje, porcentaje y valor ADC).

---

## Materiales Utilizados
* Display LCD de 16x2
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V
* 3 x Botones (Pulsadores)
* 2 x Potenciómetros de 10kΩ (Para variar las entradas analógicas)
* 1 x Potenciómetro de 1kΩ (Para controlar el contraste/brillo de la pantalla LCD)

---

## Resultados

El desarrollo de la práctica se estructuró en dos fases operativas para dominar la lectura de múltiples canales analógicos y la navegación de menús con múltiples botones.

### Actividad de Clase: Lectura Simultánea (Simulación)
Se configuraron los puertos analógicos RA0 y RA1 como entradas independientes, cada una conectada a un potenciómetro. En la simulación, se logró medir ambos voltajes y mostrarlos simultáneamente en la pantalla LCD (el voltaje 1 en la primera fila y el voltaje 2 en la segunda fila).

### Actividad 1: Interfaz de Medición Avanzada
Se trasladó el circuito al entorno físico, implementando un sistema de navegación más complejo mediante interrupciones externas. El sistema utiliza botones para controlar qué información se muestra en la pantalla:
* **Botón de Métrica:** Al presionarlo, cambia la pantalla actual mostrando: Voltaje (0V - 5V), Porcentaje (0% - 100%) o el valor crudo del ADC (0 - 1023).
* **Botón de Canal:** Al presionarlo, conmuta entre la lectura del potenciómetro conectado en **RA0** y el de **RA1**, permitiendo analizar ambos canales por separado con sus respectivas métricas en la misma interfaz.

A continuación se presentan las evidencias y la estructura de las interfaces logradas:

| Simulación (Actividad de Clase) | Armado Físico (Actividad 1) |
| :---: | :---: |
|<img width="1110" height="501" alt="image" src="https://github.com/user-attachments/assets/f7a8bc5e-90a7-4851-b550-2d6efd15aedd" />|<img width="3072" height="4096" alt="IMG_20260612_160455" src="https://github.com/user-attachments/assets/bc302780-781e-4792-8143-81a37f704c2f" />|

| Interfaz de Visualización | Descripción de la Pantalla | Evidencia (RA0 / RA1) |
| :--- | :--- | :---: |
| **Monitoreo Completo (Voltaje, Porcentaje y ADC)** | Muestra de forma integrada o secuencial el voltaje calculado, su representación en porcentaje (0-100%) y el valor de la conversión digital (0-1023) para la entrada analógica seleccionada (RA0 o RA1). |<img width="237" height="421" alt="VID_20260612_160425 (1)" src="https://github.com/user-attachments/assets/ed719ec5-17bd-4b28-b872-66c1ac031f01" />|

---

## Conclusiones

Juan:

Durante esta práctica pude afianzar los conocimientos que la actividad #6 y #7 me dieron, ajustando los detalles en los que antes se había fallado. Por esto, creo que la práctica fue de gran importancia para poder comprender cómo emplear de manera correcta una pantalla LCD, así como sus requerimentos (en términos de código), para su correcto funcionamiento.

Erick:

Esta práctica fue clave para comprender cómo el microcontrolador puede gestionar múltiples señales del mundo real utilizando un solo módulo ADC. Al trabajar con el PIC16F887, aprendí la importancia de cambiar correctamente el canal de lectura en los registros internos (conmutando entre RA0 y RA1) y dar el tiempo necesario para que el capacitor de muestreo se estabilice.
