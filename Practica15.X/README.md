<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">COMUNICACIÓN ENTRE MICROPROCESADORES</h1>
  <p style="color: #888; font-family: monospace;">Práctica #15</p>
</div>

## Objetivo Principal
Establecer y comprender la comunicación bidireccional o unidireccional entre dos microcontroladores PIC16F887 utilizando sus módulos de transmisión y recepción. El propósito es enviar una señal de control desde un microcontrolador maestro (emisor) mediante una entrada física, para accionar un componente de salida en un microcontrolador esclavo (receptor).

---

## Materiales Utilizados
* 2 Microcontroladores PIC16F887
* 1 Botón (Pulsador)
* 1 LED
* Protoboard
* Fuente de alimentación de 5V

---

## Resultados

Durante el desarrollo de la práctica se configuraron los puertos de comunicación serial de ambos microcontroladores, logrando la interacción física entre dos sistemas independientes.

### Actividad de Clase: Control a Distancia (Emisor-Receptor)
Se realizó un programa estructurado donde se conectaron los puertos de transmisión (TX) del primer PIC con los puertos de recepción (RX) del segundo PIC. El sistema funciona de la siguiente manera: al presionar el botón en el circuito del primer microcontrolador, este envía una trama de datos o señal al segundo microcontrolador. Al recibir y decodificar esta señal, el segundo PIC ejecuta la instrucción de encender el LED conectado a sus puertos de salida.

A continuación, se presenta la tabla para los diagramas y evidencias visuales de la conexión y el funcionamiento:

| Descripción del Circuito | Diagrama de Conexión (Proteus) | Evidencia de Funcionamiento (Físico) |
| :--- | :---: | :---: |
| **Comunicación TX/RX con PIC16F887** | `[Insertar imagen del diagrama aquí]` | `[Insertar foto/video del armado aquí]` |

---

## Conclusiones

**Erick:**
[Insertar detalle aquí]

**Juan:**
[Insertar detalle aquí]
