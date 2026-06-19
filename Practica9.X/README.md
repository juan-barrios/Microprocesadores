<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">INTERRUPCIONES INTERNAS (TIMER0)</h1>
  <p style="color: #888; font-family: monospace;">Práctica #9</p>
</div>

## Objetivo Principal
Comprender e implementar el uso de las interrupciones internas del microcontrolador PIC16F887 mediante el módulo **Timer0**. Se busca generar una base de tiempo precisa para construir un reloj en formato de 12 horas sin depender de retardos bloqueantes (como `__delay_ms()`). Además, se integrará de manera concurrente la lectura analógica de un voltaje, mostrando ambas informaciones (tiempo y voltaje) distribuidas estratégicamente en un display LCD.

---

## Materiales Utilizados
* Display LCD de 16x2
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V
* 1 x Botón (Pulsador)
* 1 x Potenciómetro de 10kΩ (Para simular la entrada analógica conectada al puerto RB0)
* 1 x Potenciómetro de 1kΩ (Para controlar el contraste/brillo de la pantalla LCD)

---

## Resultados

La práctica se dividió en dos etapas fundamentales que permitieron integrar el manejo de tiempos por hardware con la conversión analógica-digital (ADC).

### Actividad de Clase: Reloj con Timer0
Se configuró el módulo Timer0 para generar interrupciones periódicas, creando así una base de tiempo exacta. Con esta base, se programó un contador estructurado como un reloj en formato de 12 horas. El uso de la interrupción interna permitió que el microcontrolador llevara la cuenta del tiempo en segundo plano, evitando la paralización del procesador que causan las instrucciones de retardo convencionales.

### Actividad 1: Integración de Reloj y Lectura Analógica
Se amplió el código de la actividad de clase para incluir la lectura del convertidor analógico a digital (ADC) utilizando el pin RB0 como entrada analógica. Se logró un sistema concurrente donde el display LCD de 16x2 muestra dos datos en tiempo real:
* **Esquina superior izquierda:** Medición del voltaje de entrada (controlado por el potenciómetro de 10kΩ).
* **Esquina inferior derecha:** Contador del reloj en formato de 12 horas actualizado por la interrupción del Timer0.

A continuación, se presentan las evidencias del diseño y funcionamiento del circuito:

| Simulación del Sistema | Armado Físico (Actividad 1) |
| :---: | :---: |
|<img width="1123" height="508" alt="image" src="https://github.com/user-attachments/assets/ca8c1a15-ec39-4902-960f-06819ec17448" />| <img width="3072" height="4096" alt="IMG_20260616_155010_1" src="https://github.com/user-attachments/assets/fc8a6669-e7b8-4b48-8b9e-775a2f5b5309" />|

| Funcionalidad | Descripción del Estado Visual | Evidencia de Funcionamiento |
| :--- | :--- | :---: |
| **Reloj (Timer0)** | Contador en formato 12H ubicado en la esquina inferior derecha. Actualización fluida sin bloqueos. |<img width="652" height="367" alt="VID_20260616_155133 (1)" src="https://github.com/user-attachments/assets/71e422b8-35cb-471d-afe7-3c450b681257" />|
| **Lectura de Voltaje** | Medición analógica en la esquina superior izquierda, operando simultáneamente con el reloj. |<img width="367" height="652" alt="VID_20260616_155014 (1)" src="https://github.com/user-attachments/assets/d4b7955e-a548-4a96-bad5-6b6184cc301a" />|

---

## Conclusiones

Juan:

Aprender a utilizar las herramientas internas que el PIC ya tiene para poder generar códigos que sean capaces de realizar acciones periódicas me pareció muy interesante, porque con cada clase que pasa no sólo seguimos aprendiendo sobre cosas que podemos realizar con el microcrontolador, además, podemos aprender sobre las capacidades internas del mismo, así como entender cómo aplicarlas a futuros proyectos.

Erick:

Esta práctica fue fundamental para entender el concepto de la programación no bloqueante y la verdadera multitarea por hardware. Al configurar el Timer0 en el PIC16F887, comprendí cómo delegar el conteo del tiempo a los periféricos internos en segundo plano, liberando al procesador principal de los retardos convencionales.
