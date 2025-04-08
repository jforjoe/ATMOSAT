# Hardware Connections for ATMOSAT

This document provides the pin connections for the **ATMOSAT** project, including the transmitter (CubeSat) and receiver (ground station) setups.

---

## 1. Transmitter (CubeSat) Connections

### Components:
- **Arduino Nano**
- **HC-12 Wireless Module**
- **MPU-6050 (Accelerometer & Gyroscope)**
- **DHT11 (Temperature & Humidity Sensor)**
- **SD Card Module**
- **3.7V LiPo Battery**

### Connections:

| **Component**       | **Arduino Nano Pin** | **Details**                                                                 |
|----------------------|----------------------|-----------------------------------------------------------------------------|
| **HC-12 Module**     |                      |                                                                             |
|                      | `TX` (Pin 3)         | HC-12 RX Pin                                                                |
|                      | `RX` (Pin 6)         | HC-12 TX Pin                                                                |
|                      | `VCC`                | 3.3V or 5V (depending on module)                                            |
|                      | `GND`                | Ground                                                                      |
| **MPU-6050**         |                      |                                                                             |
|                      | `SCL` (A5)           | I2C Clock                                                                   |
|                      | `SDA` (A4)           | I2C Data                                                                    |
|                      | `VCC`                | 3.3V or 5V                                                                  |
|                      | `GND`                | Ground                                                                      |
| **DHT11**            |                      |                                                                             |
|                      | `Data` (Pin 2)       | Digital Pin for DHT11 Data                                                  |
|                      | `VCC`                | 3.3V or 5V                                                                  |
|                      | `GND`                | Ground                                                                      |
| **SD Card Module**   |                      |                                                                             |
|                      | `CS` (Pin 10)        | Chip Select for SPI Communication                                           |
|                      | `MOSI` (Pin 11)      | Master Out Slave In                                                         |
|                      | `MISO` (Pin 12)      | Master In Slave Out                                                         |
|                      | `SCK` (Pin 13)       | Serial Clock                                                                |
|                      | `VCC`                | 5V                                                                          |
|                      | `GND`                | Ground                                                                      |
| **LiPo Battery**     |                      |                                                                             |
|                      | `VCC`                | Connect to Arduino Nano `Vin` (if using a 3.7V LiPo battery with a boost converter) |
|                      | `GND`                | Ground                                                                      |

---

## 2. Receiver (Ground Station) Connections

### Components:
- **Arduino Nano**
- **HC-12 Wireless Module**

### Connections:

| **Component**       | **Arduino Nano Pin** | **Details**                                                                 |
|----------------------|----------------------|-----------------------------------------------------------------------------|
| **HC-12 Module**     |                      |                                                                             |
|                      | `TX` (Pin 2)         | HC-12 RX Pin                                                                |
|                      | `RX` (Pin 3)         | HC-12 TX Pin                                                                |
|                      | `VCC`                | 3.3V or 5V (depending on module)                                            |
|                      | `GND`                | Ground                                                                      |
| **Set Pin**          | `Pin 4`              | Used to configure HC-12 module (optional)                                   |

---

## 3. Power Supply
- The **Arduino Nano** can be powered via the `Vin` pin (7-12V) or the `5V` pin (if using a regulated 5V supply).
- The **HC-12 module** can be powered with 3.3V or 5V, depending on the module specifications.
- The **MPU-6050** and **DHT11** sensors can be powered with 3.3V or 5V.
- The **SD Card Module** requires 5V for proper operation.

---

## 4. Notes
- Ensure that all **GND** pins are connected to a common ground.
- Use appropriate resistors or voltage regulators if necessary to avoid damaging components.
- For long-range communication, ensure the HC-12 module has a clear line of sight and minimal interference.

