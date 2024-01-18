# Fingerprint-Based-Attendance-System-Arduino
Arduino-based Fingerprint Attendance System with Real-Time Clock (RTC) and EEPROM storage. This project utilizes Adafruit_Fingerprint, LiquidCrystal_I2C, SoftwareSerial, and virtuabotixRTC libraries to implement a biometric attendance solution. Users can enroll, delete, and register attendance through a fingerprint sensor.


## Overview

This Arduino project implements a biometric attendance system using an Adafruit fingerprint sensor, EEPROM for data storage, and a Real-Time Clock (RTC) module. The system allows users to enroll fingerprints, delete fingerprints, and log attendance with timestamps.

## Features

- Fingerprint enrollment and verification
- Attendance logging with date and time stamps
- User-friendly interface using an LCD display
- System reset and data download functionality
- Flexible user management with the ability to enroll and delete fingerprints

## Components Used

- Adafruit Fingerprint Sensor
- EEPROM (Electrically Erasable Programmable Read-Only Memory)
- LiquidCrystal_I2C for I2C communication with the LCD
- SoftwareSerial for communication with the fingerprint sensor
- virtuabotixRTC for interfacing with the Real-Time Clock
- Wire for I2C communication

## Getting Started

Follow these steps to set up and use the biometric attendance system:

### 1. Hardware Setup

- Connect the Adafruit fingerprint sensor, EEPROM, LCD, and RTC to the Arduino according to the wiring specified in your code.

### 2. Install Required Libraries

Make sure to install the necessary Arduino libraries:

```bash
# Example using Arduino IDE Library Manager
Sketch -> Include Library -> Manage Libraries -> Search and Install each library
- Adafruit_Fingerprint
- LiquidCrystal_I2C
- SoftwareSerial
- virtuabotixRTC

