<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">PROYECTO PRIMER PARCIAL: VIDEOJUEGO CON JOYSTICK</h1>
  <p style="color: #888; font-family: monospace;">Práctica #9</p>
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
| <img width="500" alt="[Insertar imagen panorámica del proyecto]" src="[Insertar enlace de imagen aquí]" /> | <img width="500" alt="[Insertar imagen detallada de conexiones]" src="[Insertar enlace de imagen aquí]" /> |

| Mecánica del Juego | Descripción Funcional | Evidencia Visual (GIF/Video/Imagen) |
| :--- | :--- | :---: |
| **Movimiento y Velocidad** | El personaje se desplaza por la cuadrícula 16x2. La velocidad responde dinámicamente al voltaje del joystick. | <img width="250" alt="[Insertar evidencia de movimiento]" src="[Insertar enlace aquí]" /> |
| **Transición de Pantalla** | El personaje cruza el borde lateral y aparece en el lado contrario de la misma fila. | <img width="250" alt="[Insertar evidencia de cruce]" src="[Insertar enlace aquí]" /> |
| **Animación de Salto** | Al presionar el botón, el personaje cambia su diseño para simular la acción de salto. | <img width="250" alt="[Insertar evidencia de salto]" src="[Insertar enlace aquí]" /> |

---

## Conclusiones

Juan:

Durante este proyecto, pude poner en práctica todo lo que he aprendido desde el inicio del curso, desde la lógica de programación del PIC, hasta el uso de canales análogos para la lectura de un "input". Es por esto que, considero que la actividad fue de gran ayuda para poder concluir con esta etapa de aprendizaje y aglomerar lo aprendido.

Erick:

