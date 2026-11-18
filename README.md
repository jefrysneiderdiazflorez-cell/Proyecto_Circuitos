# Sistema embebido de riego automático – Invernadero USB Bogotá

## Descripción
Sistema que riega las plantas del invernadero de la Universidad de San Buenaventura, sede Bogotá, según la humedad del suelo. Incluye un pulsador de riego manual con prioridad sobre el sensor y reporta su estado por comunicación serial. Está montado sobre una maqueta a escala [COMPLETAR: escala].

## Problemática
El invernadero está entre dos edificios del campus y tiene unas 50 plantas, que se riegan de 2 a 3 días por semana. El riego depende de personal de vegetación, limpieza y mantenimiento y de semilleros de investigación, lo que exige presencia humana constante, dificulta dosificar el agua y expone las plantas a la sobrehidratación y al desperdicio de agua. Fotos en `Invernadero_1.jpg` y `Invernadero_2.jpg`.

## Componentes
| Componente | Función |
|---|---|
| Arduino Mega 2560 | Microcontrolador |
| Sensor de humedad YL-69 (salida digital) | Entrada: suelo seco o húmedo |
| Pulsador + resistencia pull-down externa de 10 kΩ | Entrada manual con prioridad |
| Módulo relé de 5 V | Conmuta la bomba |
| Mini bomba sumergible 3–6 V | Actuador 1: riego |
| Buzzer | Actuador 2: aviso al cambiar de estado |
| Portapilas con 4 pilas AA | Alimentación de la bomba |
| Comunicación UART (9600 baudios) | Reporte al monitor serial |

El potenciómetro que aparece en algunas fotos se usó solo durante las pruebas (el sensor era muy sensible) y no es parte del diseño final.

## Conexiones
| Componente | Pin |
|---|---|
| Pulsador | D2 |
| Sensor YL-69 (DO) | D6 |
| Relé (IN) | D3 |
| Buzzer | D8 |

Diagrama de conexiones (simulación en Tinkercad): `simulacion_tinkercad.jpg`.
La simulación usa un Arduino Uno y una batería de 9 V; el montaje físico usa un Mega 2560 y pilas AA.

## Instrucciones de uso
1. Abrir `riego_usb.ino` en Arduino IDE y cargarlo en la placa.
2. Abrir el Monitor Serial a 9600 baudios.
3. La bomba se enciende con el suelo seco o al presionar el pulsador, y se apaga con el suelo húmedo y el pulsador libre. El buzzer suena al cambiar de estado.

## Autores
Angel Figueredo, Jefry Diaz, Mario Ruiz, Carlos Sandoval
