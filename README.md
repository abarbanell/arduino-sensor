# Arduiono sketches to read sensor data

## sensor-json

Read input from a DHT-22 sensor (ari temperature and humidity) and a soil hygrometer sensor and send as JSON message over serial port. 

This is very simplistic, it will always have power on the soil hygrometer (leading to faster than necessary galvanic corrosion) 

## soil-echo

an improved variant of the sensor-json

- only measure soild sensor (on Analog A7)
- only power up the soil hygrometer for a second before taking measurement (on D7)
- blink the on-board LED while taking measurement (on D13)

only take measurement if any character is sent via serial. Measure once per character (excluding CR) 


