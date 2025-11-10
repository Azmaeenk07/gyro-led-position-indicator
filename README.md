# Gyro → LED Position Indicator

An embedded orientation-visualization system that reads real-time tilt data from an MPU6050 accelerometer and displays position on an 8x8 MAX7219 LED matrix.

**Developed as part of Albertaloop Electrical Team onboarding (Fall 2025)**

## Hardware Components
- Arduino Mega 2560 R3
- MPU6050 (GY-521) Accelerometer/Gyroscope Module  
- MAX7219 8x8 LED Matrix Display
- Breadboard & jumper wires

## Features
- Real-time tilt-to-LED position mapping
- Custom coordinate mapping algorithm
- Hardware DLPF + software debounce for stability
- I2C communication (sensor) + SPI protocol (LED matrix)
- Calibrated sensor parameters (±2g, 250°/s, 21 Hz bandwidth)

## Wiring Diagram
**I2C (MPU6050):**
- SDA → A4
- SCL → A5
- VCC → 5V
- GND → GND

**SPI (MAX7219):**
- DIN → D11
- CLK → D13
- CS → D10
- VCC → 5V
- GND → GND

## Libraries Required
```cpp
#include <Adafruit_MPU6050.h>
#include <LedControl.h>
```

Install via Arduino Library Manager

## Usage
1. Upload code to Arduino Mega 2560
2. Tilt the board to see LED indicator move across matrix
3. Level board to see centered position

## Demo
[Optional: Add a photo or video here later]

## Author
Azmaeen Kaikobad  
Mechatronics & Robotics Engineering, University of Alberta  
[LinkedIn](https://www.linkedin.com/in/azmaeenk)
