<div align="center" style="background-color: #1e1e1e; padding: 20px; border-radius: 8px; border: 1px solid #333;">
  <kbd>Microprocesadores</kbd>
  <h1 style="color: #00ff66; font-family: monospace; margin-top: 10px;">DISPLAY 7 SEGMENTOS</h1>
  <p style="color: #888; font-family: monospace;">Práctica #3</p>
</div>

## Objetivo Principal
Programar y comprender el funcionamiento de un display de 7 segmentos en configuración de cátodo común, utilizando el microcontrolador PIC16F887 para visualizar secuencias de dígitos en formato decimal (0-9) y hexadecimal (0-F).

---

## Materiales Utilizados
* Display 7 segmentos (Cátodo Común)
* Microcontrolador PIC16F887
* Protoboard
* Fuente de alimentación de 5V

---

## Resultados

Durante el desarrollo de esta práctica se completaron satisfactoriamente dos actividades principales orientadas a la manipulación de los puertos de salida del microcontrolador.

### Actividad 1 y 2: Secuencias Decimal y Hexadecimal
Se logró mostrar la secuencia numérica del **0 al 9** (Actividad 1) y posteriormente se extendió el código para mostrar los dígitos del **0 al F** en hexadecimal (Actividad 2). 

A continuación, se presenta la tabla de conversión utilizada en el procedimiento para determinar los valores a enviar al puerto del microcontrolador. *(Nota: Se asume que el orden de los bits del puerto va del bit 7 al bit 0, correspondiendo a `a, b, c, d, e, f, g, dp`)*.

| Dígito / Carácter | Segmentos a encender (a,b,c,d,e,f,g,dp) | Valor Binario | Valor Hexadecimal |
| :---: | :---: | :---: | :---: |
| **0** | `1,1,1,1,1,1,0,0` | `0b11111100` | `0xFC` |
| **1** | `0,1,1,0,0,0,0,0` | `0b0110000` | `0x60` |
| **2** | `0,1,0,1,1,0,1,1` | `0b01011011` | `0xDA` |
| **3** | `0,1,0,0,1,1,1,1` | `0b01001111` | `0xF2` |
| **4** | `0,1,1,0,0,1,1,0` | `0b01100110` | `0x66` |
| **5** | `0,1,1,0,1,1,0,1` | `0b01101101` | `0xB6` |
| **6** | `0,1,1,1,1,1,0,1` | `0b01111101` | `0xBE` |
| **7** | `0,0,0,0,0,1,1,1` | `0b00000111` | `0xE0` |
| **8** | `0,1,1,1,1,1,1,1` | `0b01111111` | `0xFE` |
| **9** | `0,1,1,0,1,1,1,1` | `0b01101111` | `0xF6` |
| **A** | `0,1,1,1,0,1,1,1` | `0b01110111` | `0xEE` |
| **B** | `0,1,1,1,1,1,0,0` | `0b01111100` | `0x3E` |
| **C** | `0,0,1,1,1,0,0,1` | `0b00111001` | `0x9C` |
| **D** | `0,1,0,1,1,1,1,0` | `0b01011110` | `0x7A` |
| **E** | `0,1,1,1,1,0,0,1` | `0b01111001` | `0x9E` |
| **F** | `0,1,1,1,0,0,0,1` | `0b01110001` | `0x8E` |

### Evidencia Fotográfica / Diagramas
<img width="3072" height="4096" alt="IMG_20260605_155506" src="https://github.com/user-attachments/assets/3bb0846c-f765-421a-859e-46c601f7cc4a" />

| Diagrama de Conexión | Actividad 1 | Actividad 2 |
| :---: | :---: | :---: |
|<img width="1006" height="450" alt="image" src="https://github.com/user-attachments/assets/87fa7a07-e0a2-421e-aac6-e99b644dcf27" />|<img width="248" height="441" alt="VID_20260605_155219 (1)" src="https://github.com/user-attachments/assets/ab144880-d171-4df1-8e71-5aa3894570a7" />|  <img width="248" height="441" alt="VID_20260605_155416 (1)" src="https://github.com/user-attachments/assets/e218badb-453a-4727-b402-ebe5bf7ecefa" />|

---

## Conclusiones
Juan:

Erick:

Esta práctica me ayudó a entender cómo se controlan los displays de 7 segmentos mediante un microcontrolador. Al trabajar con la configuración de cátodo común en el PIC16F887, aprendí a traducir números decimales y letras hexadecimales a código binario para encender los segmentos correctos de forma ordenada. Crear la tabla de conversión del 0 al F y ver el resultado en físico me demostró cómo los puertos de salida del microcontrolador manejan la información digital para interactuar con el mundo real de manera visual y clara
