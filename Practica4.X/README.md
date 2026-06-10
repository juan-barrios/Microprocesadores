<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">CONVERSIÓN DE PUERTOS DE ANALÓGICO A DIGITAL</h1>
  <p style="color: #888; font-family: monospace;">Práctica #4</p>
</div>

## Objetivo Principal
Diseñar e implementar un sistema de control y conteo utilizando el microcontrolador PIC16F887 mediante la lectura de entradas digitales (botones) y la salida de datos hacia Displays. Se busca dominar la configuración de puertos de entrada/salida (Puertos B, C y D) para desarrollar la lógica de un contador cíclico de dos dígitos (0-99) con funciones de incremento, decremento y multiplicadores.

---

## Materiales Utilizados
* 2 x Displays 7 segmentos (Cátodo Común)
* 3 x Botones
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V

---

## Resultados

Durante el desarrollo de esta práctica, se llevaron a cabo dos actividades enfocadas en la interacción entre los puertos de entrada (lectura de botones) y los puertos de salida.

### Actividad de Clase: Control de LEDs
Se configuró el microcontrolador para leer las señales de entrada de tres botones físicos. Mediante esta lectura, se logró encender de manera individual y correspondiente tres LEDs diferentes (un LED por cada botón accionado). 

### Actividad 1: Contador Cíclico 0-99 con Multiplicador
Se programó un contador de dos dígitos, mostrando el resultado en displays. El sistema opera bajo las siguientes reglas lógicas:

1. **Gestión de Puertos:** * **Puerto B:** Configurado como entrada para leer el estado de los tres botones de control.
   * **Puerto C:** Configurado como salida para controlar el display de las **decenas**.
   * **Puerto D:** Configurado como salida para controlar el display de las **unidades**.
2. **Lógica de Conteo:** El sistema permite sumar o restar al valor actual mostrado en los displays.
3. **Multiplicador de Paso:** Un tercer botón activa un "multiplicador". Al estar activo, las sumas y restas se realizan de dos en dos (±2) en lugar de uno en uno (±1).
4. **Ciclo Infinito :** El contador tiene límites en 00 y 99. Si el valor está en 99 y se incrementa, el sistema reinicia el conteo en 00. De igual forma, si está en 00 y se decrementa, el valor pasa a 99.

### Evidencia Fotográfica / Diagramas

| Descripción de la Evidencia | Imagen / Video |
| :--- | :---: |
| **Diagrama de Conexión (Proteus)** | <img width="1174" height="647" alt="image" src="https://github.com/user-attachments/assets/a866a230-f89a-4d87-9100-7bf8d181db64" />|
| **Actividad de Clase (3 LEDs y 3 Botones)** | <img width="291" height="517" alt="VID_20260608_161150 (1)" src="https://github.com/user-attachments/assets/3f97288b-af9f-4a9f-b286-358723569a36" />|
| **Actividad 1 (Contador 0-99 Funcionando)** | <img width="280" height="498" alt="VID_20260608_160820 (2)" src="https://github.com/user-attachments/assets/d56c5391-a1ba-4914-90bc-e3fa697a8961" />|

---

## Conclusiones

Juan:


Erick:

Esta práctica me permitió entender cómo coordinar entradas y salidas simultáneas en el PIC16F887 para crear un sistema interactivo. Lo más interesante fue programar la lógica del contador para que las decenas y las unidades se actualizaran de forma independiente en los puertos C y D. Además, implementar las condiciones de ciclo infinito (pasar de 99 a 00 y viceversa) y el botón multiplicador me ayudó a comprender cómo estructurar algoritmos de control más avanzados basados en las decisiones del usuario en tiempo real.
