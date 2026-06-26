<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">SIMULADOR DE ELEVADOR</h1>
  <p style="color: #888; font-family: monospace;">Práctica Final</p>
</div>

## Objetivo Principal
Diseñar, programar e implementar un sistema embebido que simule el funcionamiento lógico y visual de un elevador multi-piso utilizando el microcontrolador PIC16F887. El sistema debe gestionar la lectura de peticiones mediante un teclado matricial, procesar las transiciones de estado, actualizar la información en tiempo real a través de una pantalla LCD 16x2 e indicar visualmente la ubicación actual mediante indicadores LED.

---

## Materiales Utilizados
* **Microcontrolador:** PIC16F887 (Microchip)
* **Dispositivo de Entrada:** Teclado matricial (Control de pisos/peticiones)
* **Actuador Visual Principal:** Pantalla LCD 16x2
* **Control Analógico:** 1 Potenciómetro de 1k$\Omega$ (Regulación de contraste del LCD)
* **Indicadores Luminosos:** 6 LEDs (Representación de los pisos)
* **Soporte Físico:** Protoboard
* **Alimentación:** Fuente de poder regulada de 5V

---

## Resultados

Durante el desarrollo de esta práctica final, se integraron con éxito múltiples periféricos de entrada y salida para lograr una simulación interactiva y en tiempo real.

### Actividad de Clase: Simulación Completa del Elevador
Se desarrolló una lógica de control capaz de interpretar las pulsaciones de las teclas como solicitudes de destino. El sistema procesa de forma secuencial los estados de movimiento (subiendo, bajando o detenido) y actualiza de manera dinámica la interfaz de usuario en el LCD.


### Evidencia Fotográfica y Diagramas
| Diagrama de Conexión (Proteus) | Armado Físico del Sistema |
| :---: | :---: |
| <img width="1092" height="777" alt="image" src="https://github.com/user-attachments/assets/922bf021-ac84-4967-9720-e630e9259300" />|<img width="3072" height="4096" alt="1782436893734" src="https://github.com/user-attachments/assets/7f165a99-2cf5-4392-a8db-887a58b052a3" />|

| Evidencia en Funcionamiento (LCD y LEDs) |
| :---: |
| <img width="326" height="183" alt="VID_20260625_150527 (1)" src="https://github.com/user-attachments/assets/c51abb94-2463-4321-a420-dad0d53d1283" />|

---

## Conclusiones

Juan:
Este proyecto final me sirvió para poder comprender de una manera más concreta los temas vistos en clase. Además de ayudarme a desarrollar habilidades de investigación, de modo que pudiera aprender sobre la programación basada en eventos, así como aspectos técnicos del PIC, que nos servirían para poder completar el proyecto.

Erick:

Este proyecto final consolidó de manera práctica mi aprendizaje en sistemas embebidos mediante el diseño de una máquina de estados finitos. El mayor reto técnico fue estructurar la lógica del código para que el PIC16F887 pudiera recibir peticiones aleatorias desde el teclado matricial, decidir el sentido de giro del elevador y actualizar simultáneamente la pantalla LCD y los LEDs indicadores sin retrasos ni pérdidas de datos.
