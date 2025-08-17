# 🤖 Obstacle Detection Robot Car

This is a simple Arduino-based robot car that detects obstacles using an ultrasonic sensor and automatically avoids them. The project uses an Arduino UNO, L298N motor driver, ultrasonic distance sensor (HC-SR04), servo motor, and four DC motors for movement.

# 📸 Project Overview
![Car Image](https://github.com/MohittSharma27/Obstacle-Detection-Car/blob/972ab9ab7054ca2d99b53b7cfac3818c50fb731c/Car_1_img.jpeg)

# 🛠️ Circuit Diagram
![Circuit Image][]
# 🧰 Components Used

Arduino UNO

L298N Motor Driver

HC-SR04 Ultrasonic Sensor

SG90 Servo Motor

4x TT Gear Motors with Wheels

2x 18650 Li-ion Batteries (7.4V Total)

Battery Holder

Switch

Jumper Wires

Chassis with mounting platform (custom LEGO-style platform)

# ⚙️ How It Works

The ultrasonic sensor (HC-SR04) mounted on a servo motor scans the environment.

The Arduino reads distance measurements and checks for obstacles.

If an obstacle is detected within a set range:

The car stops.

The servo rotates the ultrasonic sensor to left and right to scan for open paths.

The car turns in the direction with the most clearance.

The L298N motor driver controls the direction and speed of the motors based on the Arduino's instructions.

# 🔌 Wiring Connections
Ultrasonic Sensor (HC-SR04)
Pin	Arduino Pin
VCC	5V
GND	GND
Trig	D9
Echo	D8
Servo Motor
Wire	Arduino Pin
Signal	D10
VCC	5V
GND	GND
L298N Motor Driver
L298N Pin	Arduino Pin
IN1	D2
IN2	D3
IN3	D4
IN4	D5
ENA (via jumper)	Always ON
ENB (via jumper)	Always ON
Motor Power (VCC)	Battery +
GND	Battery - / Arduino GND
5V Output	Not connected to Arduino
