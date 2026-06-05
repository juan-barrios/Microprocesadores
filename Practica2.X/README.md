<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd> Microcrontoladores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">MATRIZ LED 8x8</h1>
  <p style="color: #888; font-family: monospace;">Practica #2 </p>
</div>

## Objetivo Principal

El objetivo principal de esta práctica es diseñar, programar e implementar el control de una matriz LED de 8x8 utilizando el microcontrolador PIC16F887. A través de este proyecto, se busca dominar la técnica de multiplexación para el encendido selectivo LEDS dentro de la matriz, permitiendo la visualización de patrones estáticos (como una señal en "X") y secuencias de caracteres alfanuméricos.

---

## Materiales Utilizados

Para el desarrollo de la práctica se emplearon los siguientes componentes y herramientas tecnológicas:

* **Microcontrolador:** PIC16F887 (Microchip)
* **Actuador Visual:** Matriz LED de 8x8
* **Soporte Físico:** Protoboard
* **Alimentación:** Fuente de poder regulada de 5V

---

## Resultados

La práctica se dividió exitosamente en dos fases operativas. Los resultados y la organización de los datos de control se detallan a continuación:

### 1. Actividad de Clase: Patrón en "X"
Se programaron los puertos del PIC16F887 para activar las coordenadas correspondientes a las diagonales de la matriz, logrando iluminar de forma fija el patrón de una "X".

### 2. Actividad de Práctica: Secuencia de Caracteres
Se implementó una secuencia lógica temporal para mostrar de manera cíclica cuatro letras correspondientes a nuestras iniciales (**J**, **B**, **E** y **H**).

A continuación se muestra la matriz de datos de diseño y los marcadores de evidencia visual:
| Proteus del Armado | Armado fisico |
| :--- | :--- |
|<img width="1424" height="736" alt="image" src="https://github.com/user-attachments/assets/6a5fd4b0-b836-41c2-9842-d59b9fb82fa6" /> |<img width="3072" height="4096" alt="IMG_20260604_165131" src="https://github.com/user-attachments/assets/5c0ffa35-5a4b-4a91-9ec8-a85b0413b3e8" />|

| Actividad / Carácter | Descripción del Estado Visual | Registro de Estado en Pines (Ejemplo) | Evidencia de Funcionamiento |
| :--- | :--- | :--- | :--- |
| **Actividad en Clase ("X")** | Encendido de las dos diagonales principales de la matriz 8x8. | `0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81` | <img width="3072" height="4096" alt="IMG_20260604_165114" src="https://github.com/user-attachments/assets/60b0129c-fcf0-4d8b-87bd-81fb94d9ac8b" />|
| **Letra J** | Primera inicial (Juan). | `0x1,0x1,0x1,0x1,0x1,0x1,0x1,0xFF` | <img width="3072" height="4096" alt="IMG_20260604_164939" src="https://github.com/user-attachments/assets/16e65566-e5c4-4062-bbb4-1b7ba5546e35"/>|
| **Letra B** | Segunda inicial (Juan). | `0xFF,0x81,0x81,0x82,0xFF,0x82,0x81,0xFF` | <img width="3072" height="4096" alt="IMG_20260604_164906" src="https://github.com/user-attachments/assets/8afa8a80-6872-42dd-9b3f-403c190c53bb" />|
| **Letra E** | Primera inicial (Erick). | `0xFF,0x80,0x80,0x80,0xFF,0x80,0x80,0xFF` | [<img width="3072" height="4096" alt="IMG_20260604_164909" src="https://github.com/user-attachments/assets/e611e983-5bd1-44eb-a5c0-721e5a8dc33c" />|
| **Letra H** | Segunda inicial (Erick). | `0x81,0x81,0x81,0x81,0xFF,0x81,0x81,0x81` | <img width="3072" height="4096" alt="IMG_20260604_164913" src="https://github.com/user-attachments/assets/7ea3f857-8961-45f3-a123-717a4feb1660" />|

---

## Conclusiones

* 
