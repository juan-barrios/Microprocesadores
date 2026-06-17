<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">PROYECTO PRIMER PARCIAL: VIDEOJUEGO CON JOYSTICK</h1>
  <p style="color: #888; font-family: monospace;">Proyecto #1</p>
</div>

## Objetivo Principal
Diseñar e implementar un sistema interactivo tipo "videojuego" utilizando el microcontrolador PIC16F887 y un display LCD de 16x2. El proyecto tiene como propósito integrar la lectura de múltiples canales analógicos para interpretar la posición de un joystick, traduciéndola en movimiento bidimensional con velocidad variable. Además, se busca aplicar lógica de programación para recrear mecánicas de pantalla continua (efecto Pac-Man) y el despliegue de animaciones mediante entradas digitales.

---

## Materiales Utilizados
* Display LCD de 16x2
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V
* 1 x Módulo Joystick (Con potenciómetros para ejes X/Y y botón integrado)
* 1 x Botón externo (Pulsador)
* 1 x Potenciómetro de 1kΩ (Para controlar el contraste/brillo de la pantalla LCD)

---

## Resultados

El desarrollo de este proyecto parcial culminó exitosamente con la creación de un entorno interactivo en la pantalla LCD. Se lograron implementar tres mecánicas principales:

1. **Movimiento y Velocidad Variable:** Se programó al microcontrolador para leer los valores analógicos de los ejes X e Y del joystick. La posición del personaje en la pantalla se actualiza en función de estos valores, logrando movimiento tanto horizontal como vertical. Además, la velocidad de desplazamiento es proporcional al grado de inclinación del joystick (a mayor inclinación, mayor velocidad).
2. **Lógica de Pantalla Continua (Wrap-around):** Se programó una condición de límites para la matriz del LCD. Si el personaje sobrepasa el límite izquierdo o derecho de la pantalla, reaparece automáticamente en el extremo opuesto, emulando la mecánica clásica del juego *Pac-Man*.
3. **Animación de Salto:** Al detectar la presión del botón (entrada digital), el sistema ejecuta una rutina que reemplaza temporalmente el carácter estático por una secuencia de caracteres personalizados, simulando visualmente un salto en la pantalla.

A continuación, se presentan las evidencias del armado y el funcionamiento de las mecánicas del juego:

| Vista General del Proyecto | Armado del Circuito Físico |
| :---: | :---: |
|<img width="1147" height="507" alt="image" src="https://github.com/user-attachments/assets/b28f6442-641b-4f78-b26f-cb0df0f310fa" />| <img width="3072" height="4096" alt="IMG_20260615_165431" src="https://github.com/user-attachments/assets/029bc2c1-c3b3-49f8-a42f-fb22eac26b1b" />|

| Mecánica del Juego | Descripción Funcional | Evidencia Visual (GIF/Video/Imagen) |
| :--- | :--- | :---: |
| **Control, Dinámica y Animación del Personaje** | Demostración del desplazamiento por la cuadrícula 16x2 con velocidad dinámica según el voltaje del joystick, el efecto de transición cíclica al cruzar los bordes laterales y la animación de salto al accionar el botón. |<img width="324" height="576" alt="VID_20260615_165435 (1)" src="https://github.com/user-attachments/assets/69f6201c-55f5-4e3b-8850-a72897ec1db1" />|

---

## Conclusiones

Juan:

Durante este proyecto, pude poner en práctica todo lo que he aprendido desde el inicio del curso, desde la lógica de programación del PIC, hasta el uso de canales análogos para la lectura de un "input". Es por esto que, considero que la actividad fue de gran ayuda para poder concluir con esta etapa de aprendizaje y aglomerar lo aprendido.

Erick:

Este proyecto fue la oportunidad perfecta para aplicar los conceptos de microprocesadores en un entorno lógico mucho más complejo y creativo. Lo más retador fue traducir las lecturas analógicas del joystick no solo a una dirección, sino a una velocidad de desplazamiento variable que se sintiera fluida en la pantalla LCD.
