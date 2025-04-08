// receiver.ino
#include <SoftwareSerial.h>
int setPin = 4;

SoftwareSerial HC12(2, 3); // HC-12 TX Pin, HC-12 RX Pin
byte incomingByte;
String readBuffer = "";

void setup() {
    Serial.begin(9600); // Open serial port to computer
    HC12.begin(9600); // Open serial port to HC12
    pinMode(setPin, OUTPUT);
    digitalWrite(setPin, LOW);
    delay(250);
    HC12.write("AT+DEFAULT");
    delay(250);
    digitalWrite(setPin, HIGH); // HC-12 normal, transparent mode
}

void loop() {
    int h = HC12.read();
    int t = HC12.read();
    int AcX = HC12.read();
    int AcY = HC12.read();
    int AcZ = HC12.read();
    int GyX = HC12.read();
    int GyY = HC12.read();
    int GyZ = HC12.read();

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
    Serial.print(" *C ");
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println(" %");
    Serial.println(" ");
    delay(1500);
}