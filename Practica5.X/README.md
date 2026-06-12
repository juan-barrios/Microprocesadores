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

### 1. Actividad de Clase 1: Botones de segmentos
Se programó un contador que contiene 3 segmentos sin encender, estos se encienden al presionar uno de 3 botones, esto con el objetivo de aprender a asignar encendido a una interacción externa.

### 2. Actividad de Clase 2: Contador con 3 botones
Se configuraron 3 botones diferentes para cumplir funciones, es un contador que al presionar el boton 1, hace incrementos de 1, si se presiona el boton 2 se hacen decrementos de 1 y si se presiona el boton 3, este funciona como un multiplicador de 2 para incrementar o disminuir de 2 en 2.

### 3. Actividad 1: Control de Dirección de Conteo
Se modificó el sistema del contador (0-9999) para responder de forma dinámica a las interrupciones externas. El contador inicia su secuencia de manera ascendente; sin embargo, cada vez que se pulsa el botón externo, se genera una interrupción que invierte la dirección lógica del conteo (cambiando de ascendente a descendente, y viceversa).

### Evidencia Fotográfica / Diagramas
<img width="3072" height="4096" alt="IMG_20260608_161227" src="https://github.com/user-attachments/assets/e3ea76a3-72b4-4b08-b627-4e273d900cca" />

| Actividad / Módulo | Descripción del Comportamiento | Evidencia Visual (Físico / Proteus) |
| :--- | :--- | :--- |
| **Botones de segmentos** | Conteo de 0 a 9999 con multiplexación estable en display de 4 dígitos. |<img width="475" height="844" alt="VID_20260608_161150+(1) (1)" src="https://github.com/user-attachments/assets/588eeb07-c008-46ba-988d-ed0e75a748ee" />|
| **Contador con 3 botones** | Detención de conteo y parpadeo secuencial de LED externo. |<img width="259" height="460" alt="VID_20260608_160820+(1) (1)" src="https://github.com/user-attachments/assets/c5f1fd0a-7c3d-4d23-8efe-c1424b52492c" />|
| **Control de Dirección** | Inversión del flujo del contador mediante la pulsación del botón. | <img width="595" height="335" alt="VID_20260609_163925 (1)" src="https://github.com/user-attachments/assets/244360d7-b689-4786-af28-c1bd83b85080" />|
| **Diagrama General** | Esquema de conexiones en Proteus. | <img width="1158" height="477" alt="image" src="https://github.com/user-attachments/assets/ebe2af6a-081b-43a6-a77f-493872bda80d" />|

---

## Conclusiones

**Juan:**

Esta fue, sin duda, una de las actividades más retadoras entre lo que llevamos realizado durante la materia, debido a que es una integración de todos los temas, desde el uso de puertos, hasta multiplexación. Por lo mismo, me sirvió bastante para poder aprender sobre técnicas como el uso de interrupciones, a manera de 'condicionales', lo que nos será muy útil para proyectos futuros.

**Erick:**

Esta práctica me sirvió para entender la diferencia fundamental entre el código secuencial y las interrupciones por hardware. Al trabajar con el PIC16F887, comprendí cómo una interrupción externa puede pausar instantáneamente el programa principal para atender un evento crítico —como cambiar el sentido del conteo o activar la rutina del LED— sin perder el control de las variables. Fue un gran reto combinar esto con la multiplexación del display de 4 dígitos, ya que me obligó a ser muy preciso con la gestión de tiempos para que el cambio de funciones no afectara la visualización en la protoboard.
