# Snapple Bot
Hi, I'm Snapple! Documenation for Snapple is below
# Snapple wiring doc

L298N (motor control):

<img width="1404" height="776" alt="image" src="https://github.com/user-attachments/assets/66add6cf-b96e-4b99-9b73-4f1cb6e45efb" />


Motor A/B: black wires: out 1 / out 4, red wires: out 2 / out 3

L298N GND -> arduino GND
L298N 5V -> arduino VIN
L298N IN1 -> arduino pin 4
L298N IN2 -> arduino pin 5
L298N IN 3 -> arduino pin 6
L298N IN 4 -> arduino pin 7
L298N ENA -> arduino pin 8
L298N ENB -> arduino pin 9

Battery (power): 
Battery red -> power switch -> L298N 12V
Battery black -> L298N GND

ESP32 (wireless connection):

ESP32 RX -> arduino red pin 0
ESP32 TX -> arduino red pin 1
ESP32 GND -> arduino GND 
ESP32 3V -> arduino 5V
