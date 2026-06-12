<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">USO DE DISPLAYS LCD</h1>
  <p style="color: #888; font-family: monospace;">Práctica #6</p>
</div>

## Objetivo Principal
Diseñar, programar e implementar el control de un display LCD de 18x2 utilizando el microcontrolador PIC16F887. A través de este proyecto, se busca dominar la manipulación de pantallas para mostrar mensajes estáticos y dinámicos, crear caracteres especiales en la memoria del dispositivo y gestionar interrupciones mediante botones externos para alternar mensajes.

---

## Materiales Utilizados
* Display LCD de 16x2
* Microcontrolador PIC16F887
* 2 Botones (Pulsadores)
* Protoboard
* Fuente de alimentación de 5V

---

## Resultados

Durante el desarrollo de la práctica, se completaron dos actividades principales enfocadas en el control del display y la gestión de entradas físicas:

### Actividad de Clase: Mensaje Estático y Secuencia Alfabética
Se programó el microcontrolador para mostrar un mensaje de texto estático en la primera fila del display LCD. Simultáneamente, en la segunda fila se implementó una secuencia dinámica donde las letras del alfabeto (desde la **A** hasta la **Q**) aparecían de una en una. Una vez completada la secuencia hasta la letra Q, la pantalla se limpiaba y el ciclo volvía a comenzar de manera automática.

### Actividad 1: Caracteres Especiales e Interrupciones Externas
Se diseñaron dos caracteres especiales personalizados guardados en la memoria del display. El funcionamiento se dividió en dos estados controlados por una interrupción de hardware (botón externo):
* **Estado Inicial:** En la primera fila se mostraba la palabra "Microprocesadores". En la segunda fila, se imprimió el mensaje "Youtube" acompañado del carácter especial diseñado con el logo de la plataforma.
* **Estado de Interrupción:** Al presionar el botón externo, el programa atendía la interrupción, borrando el mensaje anterior y mostrando en la primera fila la palabra "Verano". En la segunda fila se mostró "MLBB" junto con un carácter especial correspondiente al logo de Mobile Legends.

A continuación, se presenta la tabla de control visual para la inserción de evidencias:
<img width="3072" height="4096" alt="IMG_20260610_165214" src="https://github.com/user-attachments/assets/b32364ef-cb10-4d2a-b033-5cbc828fea4b" />


| Actividad / Estado | Descripción del Comportamiento | Evidencia de Funcionamiento |
| :--- | :--- | :--- |
| **Actividad en Clase** | Fila 1: Mensaje fijo. Fila 2: Letras A-Q en aparición secuencial cíclica. |<img width="572" height="1017" alt="VID_20260610_165257 (1)" src="https://github.com/user-attachments/assets/c606fd1b-345d-46a3-aa63-a30e883b8c3f" />|
| **Actividad 1 Caracteres Especiales e Interrupciones Externas)** | Fila 1: "Microprocesadores". Fila 2: "[Logo YouTube] Youtube". |<img width="572" height="1017" alt="VID_20260610_165203 (1)" src="https://github.com/user-attachments/assets/46d75b54-0952-4673-afa1-5cbd6fc99791" />|

---

## Conclusiones

Juan:

Esta fue la práctica más retadora hasta el momento, no debido a temas de programación, más bien, por el armado físico del circuito, debido a dificultades que tuvimos en donde no se mostrana correctamente el mensaje, a pesar de que la simulación fuera correcta. Algunos aprendizajes que pude obtener fue el factor de la resiliencia y el pensamiento crítico, ambos fueron claves para entender el problema y resolverlo.

Erick:


Esta práctica me demostró la gran diferencia que existe entre la teoría de una simulación y el comportamiento real de los componentes. El mayor reto no fue el código, sino diagnosticar y corregir los problemas en el armado físico para que el LCD inicializara y mostrara los datos correctamente. Superar esto me permitió entender a fondo la importancia de los tiempos de espera y las conexiones físicas en las pantallas.
