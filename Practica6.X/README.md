<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">USO DE DISPLAYS LCD</h1>
  <p style="color: #888; font-family: monospace;">Práctica #6</p>
</div>

## Objetivo Principal
Diseñar, programar e implementar el control de un display LCD de 18x2 utilizando el microcontrolador PIC16F887. A través de este proyecto, se busca dominar la manipulación de pantallas para mostrar mensajes estáticos y dinámicos, crear caracteres especiales en la memoria del dispositivo y gestionar interrupciones mediante botones externos para alternar mensajes.

---

## Materiales Utilizados
* Display LCD de 18x2
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

| Actividad / Estado | Descripción del Comportamiento | Evidencia de Funcionamiento |
| :--- | :--- | :--- |
| **Actividad en Clase** | Fila 1: Mensaje fijo. Fila 2: Letras A-Q en aparición secuencial cíclica. | `[Insertar imagen o GIF aquí]` |
| **Actividad 1 (Predeterminado)** | Fila 1: "Microprocesadores". Fila 2: "[Logo YouTube] Youtube". | `[Insertar imagen o GIF aquí]` |
| **Actividad 1 (Interrupción)** | Fila 1: "Verano". Fila 2: "[Logo ML] MLBB" (Activado mediante botón). | `[Insertar imagen o GIF aquí]` |

---

## Conclusiones

Juan:

Esta fue la práctica más retadora hasta el momento, no debido a temas de programación, más bien, por el armado físico del circuito, debido a dificultades que tuvimos en donde no se mostrana correctamente el mensaje, a pesar de que la simulación fuera correcta. Algunos aprendizajes que pude obtener fue el factor de la resiliencia y el pensamiento crítico, ambos fueron claves para entender el problema y resolverlo.

Erick:
