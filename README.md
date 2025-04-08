# ATMOSAT Project

This project involves the development of a CubeSat-based weather monitoring system called **ATMOSAT**. The system is equipped with sensors to measure temperature, humidity, pressure, and acceleration. The data is transmitted wirelessly using the HC-12 module and stored on an SD card.

## Folder Structure
- **Transmitter**: Contains the code for the ATMOSAT CubeSat.
- **Receiver**: Contains the code for the ground station receiver.

## Hardware Components
- Arduino Nano
- HC-12 Wireless Module
- MPU-6050 (Accelerometer & Gyroscope)
- DHT11 (Temperature & Humidity Sensor)
- SD Card Module
- 3.7V LiPo Battery

## Libraries Used
- Wire.h
- DHT.h
- SD.h
- SoftwareSerial.h
- avr/sleep.h

## How to Use
1. Upload the `transmitter.ino` code to the ATMOSAT CubeSat.
2. Upload the `receiver.ino` code to the ground station Arduino.
3. Power on both devices and monitor the data on the receiver's serial monitor.

## License
This project is open-source and available under the MIT License.