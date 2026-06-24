<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">TECLADO MATRICIAL</h1>
  <p style="color: #888; font-family: monospace;">Práctica #12</p>
</div>

## Objetivo Principal
Implementar la lectura y decodificación de un teclado matricial de 4x4 utilizando los puertos digitales del microcontrolador PIC16F887. Se busca dominar la técnica de escaneo por filas y columnas para capturar datos de entrada del usuario, visualizarlos en una pantalla LCD de 16x2 y, mediante lógica de programación avanzada, procesar esta información para diseñar una calculadora aritmética funcional con precisión decimal.

---

## Materiales Utilizados
* Microcontrolador PIC16F887
* Display LCD de 16x2
* Teclado matricial de 4x4
* Protoboard
* Fuente de alimentación de 5V
* 1 x Botón (Pulsador)
* 1 x Potenciómetro de 1kΩ (Para modular el contraste/brillo de la pantalla LCD)

---

## Resultados

El proyecto se estructuró en dos etapas progresivas, partiendo desde el reconocimiento básico de las teclas hasta la implementación de algoritmos matemáticos en el microcontrolador.

### Actividad de Clase: Interfaz Teclado - LCD
Se desarrolló el algoritmo de escaneo (multiplexación) para leer el teclado matricial 4x4. Al detectar la pulsación de una tecla, el microcontrolador identifica la intersección exacta de la fila y la columna, mapeando este evento a su carácter correspondiente (números del 0 al 9 y letras de la A a la D, asterisco y numeral). El carácter identificado se imprime exitosamente en tiempo real en la pantalla LCD.

### Actividad 1: Calculadora con Precisión Decimal
Tomando como base la lectura de caracteres de la actividad de clase, se programó la lógica completa de una calculadora matemática. El sistema permite al usuario ingresar de forma secuencial un primer número, un operador aritmético (suma, resta, multiplicación o división) y un segundo número. Al ejecutar la operación, el PIC16F887 procesa el cálculo y despliega el resultado en el display LCD, garantizando una visualización exacta con hasta dos puntos decimales de precisión.

A continuación, se presentan los espacios de evidencia visual para el sistema desarrollado:

| Visualización en Proteus / Simulación | Armado Físico en Protoboard |
| :---: | :---: |
|<img width="997" height="708" alt="image" src="https://github.com/user-attachments/assets/fce2ceee-df5a-4c1c-826c-85c27930dc3a" />|<img width="3072" height="4096" alt="1782315317237" src="https://github.com/user-attachments/assets/5cf411e7-2ce4-4ad2-b6be-79f7f476e696" />|

| Funcionalidad | Descripción del Comportamiento Visual | Evidencia de Funcionamiento |
| :--- | :--- | :---: |
| **Lectura de Caracteres** | Muestra en pantalla la tecla presionada de manera instantánea. |<img width="248" height="441" alt="VID_20260623_145316 (1)" src="https://github.com/user-attachments/assets/3bc720f1-3df9-406b-957a-c19592a35129" />|
| **Operación de Calculadora** | Visualización de la sintaxis ingresada (Ej. "5 * 3") y el resultado final numérico con decimales (Ej. "15.00"). |<img width="248" height="441" alt="VID_20260623_144202 (1)" src="https://github.com/user-attachments/assets/8800e6ac-6984-4d57-827a-7902bc2cbcd0" />|

---

## Conclusiones

Juan:

Aprender de manera autogestionada sobre el uso de componentes distintos a los vistos en otras prácticas fue, sin duda, uno de los mayores retos. Lo anterior puesto que, para poder realizar la programación y leer los datos provenientes desde el teclado fue una experiencia distinta, y que me ayudó a comprender mejor cómo emplear el PIC para realizar diversas tareas. 

Erick:

Esta práctica me permitió entender a fondo la técnica de escaneo por multiplexación para la lectura de periféricos de entrada. Controlar el teclado matricial de 4x4 con el PIC16F887 me demostró cómo optimizar pines, usando solo 8 líneas de código para leer 16 botones diferentes.
