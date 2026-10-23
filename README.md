
# Line-Follower Robot

**Academic Embedded Systems Project — Ibn Zohr University**

## Overview
An Arduino-based robot that follows a black line using three analog sensors. It uses threshold-based detection and differential motor-speed control to make smooth left and right turns.

## Features
- Three-sensor line detection (left, middle, and right)
- Adjustable sensor threshold and motor speeds
- Differential motor control for turning
- Serial Monitor diagnostics at 9600 baud
- Stop behavior when the line is lost or all three sensors detect black

## Hardware & Software
- Arduino-compatible board
- Three analog line sensors
- Two DC motors and an AFMotor-compatible motor driver
- Arduino IDE and AFMotor library

## Pin Configuration

| Component | Connection |
|---|---|
| Left sensor | A0 |
| Right sensor | A1 |
| Middle sensor | A2 |
| Left motor | Motor port 1 |
| Right motor | Motor port 2 |

The sensor threshold is initially set to 500 and may need calibration for different sensors and tracks.

