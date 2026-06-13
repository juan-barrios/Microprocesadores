<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">MÚLTIPLES ENTRADAS ANALÓGICAS</h1>
  <p style="color: #888; font-family: monospace;">Práctica #8</p>
</div>

## Objetivo Principal
Diseñar e implementar un sistema de adquisición de datos para múltiples canales utilizando el convertidor analógico a digital (ADC) del microcontrolador PIC16F887. Se busca medir dos señales de voltaje de manera independiente (pines RA0 y RA1), y desarrollar una interfaz interactiva en un display LCD mediante el uso de interrupciones externas, permitiendo al usuario alternar tanto la fuente de lectura como el formato de visualización (voltaje, porcentaje y valor ADC).

---

## Materiales Utilizados
* Display LCD de 18x2
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
| <img width="500" alt="[Insertar imagen de simulación mostrando V1 y V2]" src="[Insertar enlace de imagen aquí]" /> | <img width="500" alt="[Insertar imagen del circuito físico]" src="[Insertar enlace de imagen aquí]" /> |

| Interfaz de Visualización | Descripción de la Pantalla | Evidencia (RA0 / RA1) |
| :--- | :--- | :---: |
| **Pantalla 1 (Voltaje)** | Muestra el voltaje calculado de la entrada seleccionada. | <img width="250" alt="[Insertar imagen]" src="[Insertar enlace aquí]" /> |
| **Pantalla 2 (Porcentaje)** | Muestra el nivel de voltaje como porcentaje (respecto a 5V). | <img width="250" alt="[Insertar imagen]" src="[Insertar enlace aquí]" /> |
| **Pantalla 3 (Valor ADC)** | Muestra el valor de conversión digital (0 a 1023). | <img width="250" alt="[Insertar imagen]" src="[Insertar enlace aquí]" /> |

---

## Conclusiones

Juan:

Durante esta práctica pude afianzar los conocimientos que la actividad #6 y #7 me dieron, ajustando los detalles en los que antes se había fallado. Por esto, creo que la práctica fue de gran importancia para poder comprender cómo emplear de manera correcta una pantalla LCD, así como sus requerimentos (en términos de código), para su correcto funcionamiento.

Erick:

