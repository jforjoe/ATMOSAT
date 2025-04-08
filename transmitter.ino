// transmitter.ino
#include <Wire.h>
#include <DHT.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <avr/sleep.h>

#define DHTTYPE DHT11 // DHT 11
#define DHTPIN 2 // data pin of DHT11 connected to D2
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial HC12(3, 6);

unsigned long previousMillis = 0;
const long interval = 10000; // restart interval in milliseconds

// MPU declarations
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// DHT11 declarations
float h = dht.readHumidity();
float t = dht.readTemperature();

// SD card declarations
const int chipSelect = 10;
File dataFile;

//variable to get the input from the station
char x;

//sleep mode for power management
char sleepMode = '0';

void setup() {
    Wire.begin();
    dht.begin();
    HC12.begin(9600);
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
    Serial.begin(9600);

    // initialize SD card
    pinMode(10, OUTPUT);
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        return;
    }
    Serial.println("Initializing SD card");
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (!dataFile) {
        Serial.println("Error opening data.txt");
    }
    dataFile.close();
}

void loop() {
    if (Serial.available() > 0) { // check if there is any data available on Serial port
        x = Serial.read(); // read the data and store it in the global variable
        Serial.println("Copy that....");
        Serial.println(x);
    }
    delay(1000);

    if (x == '0' || x == '1') {
        sleepMode = x;
    }

    if (sleepMode == '0') {
        sleepNow(); // Put the Arduino to sleep
        if (Serial.available() > 0) { // check if there is any data available on Serial port
            x = Serial.read(); // read the data and store it in the global variable
            Serial.println("Copy that......");
        }
    } else {
        // Receive command over HC-12 to wake up from sleep mode
        if (HC12.available()) {
            char command = HC12.read();
            if (command == '1') {
                Serial.println("Wake up command received");
                sleepMode = '1'; // Set sleep mode to false
            }
        }

        float h = dht.readHumidity();
        float t = dht.readTemperature();

        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }

        HC12.write(h);
        HC12.write(t);

        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
        AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
        AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

        HC12.write(AcX);
        HC12.write(AcY);
        HC12.write(AcZ);
        HC12.write(GyX);
        HC12.write(GyY);
        HC12.write(GyZ);

        // Print the values to the serial monitor
        Serial.print("Accelerometer: ");
        Serial.print(AcX); Serial.print(", ");
        Serial.print(AcY); Serial.print(", ");
        Serial.println(AcZ);
        Serial.print("Gyroscope: ");
        Serial.print(GyX); Serial.print(", ");
        Serial.print(GyY); Serial.print(", ");
        Serial.println(GyZ);
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.print("*C ");
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.println(" %");
        Serial.println(" ");

        if (x == 'w') {
            Store(t, h, AcX, AcY, GyX, GyY);
        } else {
            dataFile.close();
        }
    }
    delay(1500); // delay for one second
}

void Store(int t, int h, int AcX, int AcY, int GyX, int GyY) {
    // Write the values to the SD card
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.print("Accelerometer: ");
        dataFile.print(AcX); dataFile.print(", ");
        dataFile.print(AcY); dataFile.print(", ");
        dataFile.println(AcZ);
        dataFile.print("Gyroscope: ");
        dataFile.print(GyX); dataFile.print(", ");
        dataFile.print(GyY); dataFile.print(", ");
        dataFile.println(GyZ);
        dataFile.print("Temperature: ");
        dataFile.print(t);
        dataFile.print(" *C ");
        dataFile.print("Humidity: ");
        dataFile.print(h);
        dataFile.println(" %");
        dataFile.println();
        dataFile.println(" ");
        Serial.println("Data Entered");
    } else {
        // if the file didn't open, print an error:
        Serial.println("Error opening data.txt");
    }
    dataFile.close();
}

void sleepNow() {
    sleep_enable(); // Enable sleep mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power down
    sleep_cpu(); // Put the CPU to sleep
    sleep_disable(); // Disable sleep mode
}