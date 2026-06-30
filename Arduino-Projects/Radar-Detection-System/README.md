# Arduino Radar Detection System

This project is an Arduino-based radar-style detection system that uses an ultrasonic sensor mounted on a servo motor to detect nearby objects.

The servo rotates the ultrasonic sensor from side to side while the Arduino measures distance at each angle. The angle and distance data are sent to a computer through serial communication and visualized using a radar-style Processing interface.

## Project Overview

The goal of this project was to simulate a basic radar scanning system using low-cost electronic components.

The system:
- Rotates an ultrasonic sensor using a servo motor
- Measures distance to nearby objects
- Sends angle and distance data over serial communication
- Displays the data on a circular radar-style interface
- Changes the scanning line from green to red when an object is detected

## Components

- Arduino Uno / ELEGOO Uno R3
- HC-SR04 ultrasonic distance sensor
- SG90 servo motor
- Breadboard
- Jumper wires
- USB cable

## Wiring

| Component | Arduino Pin |
|---|---|
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| HC-SR04 TRIG | Digital pin 2 |
| HC-SR04 ECHO | Digital pin 9 |
| Servo signal | Digital pin 12 |
| Servo VCC | 5V |
| Servo GND | GND |

## Files

- [`radar_scanner.ino`](./radar_scanner.ino) — Arduino code for controlling the servo and ultrasonic sensor
- [`radar_display_processing.pde`](./radar_display_processing.pde) — Processing code for the radar visualization
- [`radar_setup_photo.png`](./radar_setup_photo.png) — photo of the physical setup
- [`radar_demo_screenshot.png`](./radar_demo_screenshot.png) — screenshot of the radar display

## How It Works

The servo motor rotates the ultrasonic sensor between 15° and 165°. At each angle, the Arduino triggers the ultrasonic sensor and measures the time it takes for the echo signal to return.

The Arduino calculates the distance using the ultrasonic travel time and sends the data to the computer in this format:

```text
angle,distance.
