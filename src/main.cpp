#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GPS.h>
//#include <WiFi.h>
//#include <HTTPClient.h>
//#include <ArduinoJson.h>

HardwareSerial mySerial(1);
Adafruit_GPS GPS(&mySerial);

Adafruit_LIS3MDL lis3mdl = Adafruit_LIS3MDL();

Servo myServo;

const float threshold = 5.0;
const float targetHeading = 0.0;


void setup() {

  Serial.begin(115200);
  Wire.begin();

  if (!lis3mdl.begin_I2C()) {
    Serial.println("Failed to find LIS3MDL chip");
    while (1);
  }
  Serial.println("LIS3MDL connected");

  //maybe delete later
  lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
  lis3mdl.setDataRate(LIS3MDL_DATARATE_10_HZ);

  mySerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17 (change later)
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);

  myServo.attach(18); // pwm pin
  myServo.write(90);


  // raising canes coordinates yum yum
  float targetLat = 44.948169;
  float targetLon = -93.236016;
}

void loop() {

  while (GPS.available()) {
    char c = GPS.read();

    if (GPS.newNMEAreceived()) {
      if (GPS.parse(GPS.lastNMEA())) {
        if (GPS.fix) {
          float currentLat = GPS.latitude;
          float currentLon = GPS.longitude;
        }
      }
    }
  }

  sensors_event_t event; 
  lis3mdl.getEvent(&event);

  float x = event.magnetic.x;
  float y = event.magnetic.y;
  float headingDeg = atan2(y, x) * 180 / PI;

  if (headingDeg < 0) {
  headingDeg += 360.0;
  }

  myServo.write(90 - headingDeg);
}