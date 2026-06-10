<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">INTERRUPCIONES EXTERNAS</h1>
  <p style="color: #888; font-family: monospace;">Práctica #5</p>
</div>

## Objetivo Principal
Implementar y comprender el manejo de interrupciones externas y la técnica de multiplexación utilizando el microcontrolador PIC16F887. El proyecto busca desarrollar un contador en un display de 4 dígitos que permita alterar su comportamiento de conteo (ascendente/descendente) y ejecutar rutinas de retardo específicas (parpadeo de un LED) al detectar estímulos físicos a través de un botón externo.

---

## Materiales Utilizados
* 1 Display de 4 dígitos de 7 segmentos (Cátodo Común)
* 1 Botón (Pulsador normalmente abierto)
* 1 LED externo (para la rutina de interrupción, sólo en la simulación)
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V

---

## Resultados

El desarrollo de esta práctica se dividió en tres fases operativas, enfocadas en dominar la multiplexación y el control del flujo del programa mediante interrupciones de hardware.

### 1. Actividad de Clase 1: Contador Multiplexado (0-9999)
Se programó un contador cíclico ascendente que recorre los valores del 0 al 9999. Al alcanzar el límite máximo, el sistema se reinicia a 0. Se implementó exitosamente la técnica de multiplexación, logrando la persistencia visual necesaria para que los cuatro dígitos parezcan estar encendidos simultáneamente sin parpadeos perceptibles.

### 2. Actividad de Clase 2: Rutina de Interrupción por Tiempo
Se configuró un botón externo para generar una interrupción en el sistema. Al pulsar el botón, el conteo principal del display se detiene inmediatamente y el microcontrolador pasa a ejecutar una rutina de 4 segundos. Durante este periodo, un LED externo parpadea exactamente 4 veces (una vez por cada segundo transcurrido) antes de reanudar la operación normal del display.

### 3. Actividad 1: Control de Dirección de Conteo
Se modificó el sistema del contador (0-9999) para responder de forma dinámica a las interrupciones externas. El contador inicia su secuencia de manera ascendente; sin embargo, cada vez que se pulsa el botón externo, se genera una interrupción que invierte la dirección lógica del conteo (cambiando de ascendente a descendente, y viceversa).

### Evidencia Fotográfica / Diagramas

| Actividad / Módulo | Descripción del Comportamiento | Evidencia Visual (Físico / Proteus) |
| :--- | :--- | :--- |
| **Contador Cíclico** | Conteo de 0 a 9999 con multiplexación estable en display de 4 dígitos. | `[Insertar imagen/video de Actividad de Clase 1 aquí]` |
| **Interrupción de 4s** | Detención de conteo y parpadeo secuencial de LED externo. | `[Insertar imagen/video de Actividad de Clase 2 aquí]` |
| **Control de Dirección** | Inversión del flujo del contador mediante la pulsación del botón. | `[Insertar imagen/video de Actividad 1 aquí]` |
| **Diagrama General** | Esquema de conexiones en Proteus. | `[Insertar imagen del diagrama esquemático aquí]` |

---

## Conclusiones

**Juan:**

Esta fue, sin duda, una de las actividades más retadoras entre lo que llevamos realizado durante la materia, debido a que es una integración de todos los temas, desde el uso de puertos, hasta multiplexación. Por lo mismo, me sirvió bastante para poder aprender sobre técnicas como el uso de interrupciones, a manera de 'condicionales', lo que nos será muy útil para proyectos futuros.

**Erick:**
