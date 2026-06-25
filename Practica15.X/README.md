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

| Descripción del Circuito | Diagrama de Conexión (Proteus)| Diagrama de conexión fisico | Evidencia de Funcionamiento (Físico) |
| :--- | :---: | :---: | :---:|
| **Comunicación TX/RX con PIC16F887** |<img width="617" height="716" alt="image" src="https://github.com/user-attachments/assets/783062fe-e781-4f16-b6e8-b5a04d0929f7" />|<img width="3072" height="4096" alt="1782359296472" src="https://github.com/user-attachments/assets/eb943d47-46ec-4759-bd39-1be975a84f17" />| <img width="864" height="486" alt="VID_20260624_154645 (1)" src="https://github.com/user-attachments/assets/5747922b-3a9c-4893-b9b2-df6767607993" />|

---

## Conclusiones

**Erick:**

Con esta práctica aprendí a implementar la comunicación serial asíncrona entre dos microcontroladores independientes. Lo más valioso fue configurar los registros del módulo EUSART para igualar la velocidad de transmisión (baudios) en ambos dispositivos.

**Juan:**


