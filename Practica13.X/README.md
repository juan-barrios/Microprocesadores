<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">CONTROL DE UN MOTOR DC</h1>
  <p style="color: #888; font-family: monospace;">Práctica #13</p>
</div>

## Objetivo Principal
Diseñar, programar e implementar un sistema de control de velocidad y sentido de giro para un motor de corriente directa (DC) utilizando el microcontrolador PIC16F887. Se busca comprender la aplicación de configuraciones de potencia mediante transistores BJT y la integración de un Puente H para la manipulación de cargas inductivas en entornos reales.

---

## Materiales Utilizados
* **Microcontrolador:** PIC16F887
* **Actuadores:** Motor DC de 5V
* **Componentes de Potencia y Control:**
  * Transistor BJT 2N2222A
  * Diodo rectificador 1N4007
  * Módulo/Circuito Puente H
* **Elementos de Entrada:**
  * 1 Potenciómetro de 1k$\Omega$ (Control de velocidad)
  * 1 Botón pulsador (Control de dirección/giro)
* **Soporte y Alimentación:**
  * Protoboard
  * Fuente de alimentación regulada de 5V

---

## Resultados

El desarrollo de la práctica se dividió de manera exitosa en dos fases de control de potencia y lógica temporal, permitiendo observar la transición desde un control unidireccional hasta uno bidireccional completo.

### 1. Actividad de Clase: Control Unidireccional por BJT
Se desarrolló un programa para controlar la velocidad del motor de DC mediante la lectura analógica de un potenciómetro. Para la etapa de potencia se utilizó una configuración con el transistor 2N2222A y un diodo rectificador 1N4007 como diodo de libre conducción (flyback) para proteger al circuito de corrientes inversas. La velocidad del motor responde proporcionalmente al impulso generado por el potenciómetro.

### 2. Actividad #1: Control Bidireccional con Puente H
Se expandió la lógica del circuito integrando un Puente H. Esta adición permitió conservar el control de velocidad por medio del potenciómetro e incorporar un botón pulsador para conmutar de manera lógica el sentido de giro del motor (horario / antihorario).

A continuación, se presentan las tablas organizacionales para el registro de datos y las evidencias multimedia de la práctica:

| Proteus del Armado (clase) | Armado Físico |
| :--- | :--- |
|<img width="902" height="507" alt="image" src="https://github.com/user-attachments/assets/6b003421-3da2-4fb0-b07b-052befa57374" />|<img width="3072" height="4096" alt="1782332638496" src="https://github.com/user-attachments/assets/1cb5db52-9171-4715-b4fe-ae4b4cc1ce31" />|

| Proteus del Armado (ACT) | Armado Físico |
| :--- | :--- |
| <img width="1171" height="448" alt="image" src="https://github.com/user-attachments/assets/7ad9fbf8-9822-4c5c-8d37-b4d17cec22df" />|<img width="3072" height="4096" alt="1782332638431" src="https://github.com/user-attachments/assets/0239b8d7-908a-4db8-a8e1-ee1c5dc2ae0b" />|

| Actividad / Fase | Descripción del Estado de Control | Evidencia de Funcionamiento |
| :--- | :--- | :--- |
| Actividad en Clase | Control de velocidad mediante transistor BJT y potenciómetro. Sentido único.|<img width="324" height="576" alt="VID_20260623_171732 (1)" src="https://github.com/user-attachments/assets/3a1d41ec-0eeb-48fc-937c-38283b968640" />|

| Actividad #1 (Giro Horario y Antihorario)| Velocidad regulada por potenciómetro. Sentido de giro directo e inverso al presionar el boton |<img width="324" height="576" alt="VID_20260623_172946 (1)" src="https://github.com/user-attachments/assets/45d36a7d-80c1-472a-8745-acc8b8512908" />|

---

## Conclusiones

Juan:


Erick:
Esta práctica me permitió entender cómo manejar cargas inductivas y control de potencia con el PIC16F887. 
En la primera fase, aprendí a usar el transistor BJT y el diodo flyback para proteger los pines del microcontrolador de los voltajes inversos del motor. Después, implementar el Puente H fue lo mas interesante.
