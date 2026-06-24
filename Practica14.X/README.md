<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
<kbd>Microprocesadores</kbd>
<h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">CONTROL DE UN SERVOMOTOR</h1>
<p style="color: #888; font-family: monospace;">Práctica #14</p>
</div>

## Objetivo Principal
Controlar la posición angular de un servomotor estándar utilizando el microcontrolador PIC16F887. Se busca comprender y aplicar la generación de señales de control precisas mediante el uso de interrupciones internas (Timer1) para lograr desplazamientos automáticos (de 0° a 180°). Posteriormente, se integrará el convertidor analógico a digital (ADC) para establecer un control manual y exacto del ángulo de giro a través de un potenciómetro.

---

## Materiales Utilizados
* Microcontrolador PIC16F887
* 1 x Servomotor
* Protoboard
* Fuente de alimentación de 5V
* 1 x Botón (Pulsador)
* 1 x Potenciómetro de 1kΩ (Para la lectura analógica de control de posición)

---

## Resultados

Durante la sesión práctica se desarrollaron dos rutinas de control enfocadas en el manejo de los anchos de pulso requeridos por el servomotor.

### Actividad de Clase: Barrido Automático con Timer1
Se implementó un programa apoyado en el manejo de interrupciones internas utilizando el módulo **Timer1**. Se calculó el desbordamiento necesario para generar una señal periódica que controlara el servomotor, logrando que este realizara un barrido automático, desplazándose suavemente desde 0° hasta 180° y retornando a su posición inicial de manera continua y sin intervención del usuario.

### Actividad 1: Control de Posición Manual (ADC)
El código de la actividad base fue modificado para sustituir el barrido automático por un sistema de respuesta interactiva. Se configuró el ADC del PIC para leer la variación de voltaje del potenciómetro de 1kΩ. Esta lectura analógica se mapeó matemáticamente para ajustar dinámicamente el ancho del pulso generado por el Timer1, otorgando al usuario el control manual, directo y preciso sobre el grado de inclinación del eje del servomotor.

A continuación, se presentan las evidencias del funcionamiento de ambas modalidades de control:

| Vista de Simulación del Pulso | Armado Físico del Circuito |
| :---: | :---: |
| <img width="812" height="512" alt="image" src="https://github.com/user-attachments/assets/9c9396f9-e759-4ad8-8b1f-3fe75f830d86" />|<img width="4096" height="3072" alt="1782331768417" src="https://github.com/user-attachments/assets/f585b81e-4d65-480a-885e-2609f71fa9e4" />|

| Modalidad de Control | Descripción del Comportamiento | Evidencia de Funcionamiento |
| :--- | :--- | :---: |
| **Barrido Automático (Clase)** | El servomotor gira de 0 a 180 grados y regresa automáticamente en un bucle continuo. | <img width="410" height="729" alt="VID_20260623_160043 (1)" src="https://github.com/user-attachments/assets/dd67d7e2-6447-4ccc-a919-73feadc27dd4" />|
| **Control Manual (Actividad 1)** | El eje del servomotor responde en tiempo real a los giros del potenciómetro. |<img width="768" height="432" alt="VID_20260623_155830 (1)" src="https://github.com/user-attachments/assets/5eb48d91-3346-4129-91ae-f6bf353d5ca0" />|

---

## Conclusiones

Juan:



Erick:

Esta práctica me permitió entender a fondo la estructura de las señales de control para servomotores y la precisión que se requiere en su gestión. Al utilizar el Timer1 de 16 bits en el PIC16F887, aprendí a calcular y generar manualmente los pulsos en microsegundos necesarios para posicionar el motor entre 0° y 180°.
