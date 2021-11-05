#include <Wire.h>
#include "rgb_lcd.h"

#include "Air_Quality_Sensor.h"

AirQualitySensor sensor(A0);

rgb_lcd lcd;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Waiting sensor");
  lcd.setCursor(0, 1);
  lcd.print("to init...");
  delay(20000);
  lcd.clear();

  if (sensor.init()) {
    lcd.print("Sensor ready.");
  } else {
    lcd.print("Sensor ERROR!");
  }
  delay(1000);
  lcd.clear();
}

void loop() {

  int quality = sensor.slope();

  if (quality == AirQualitySensor::FORCE_SIGNAL) {
    lcd.setRGB(255, 0, 0);

    lcd.setCursor(0, 0);
    lcd.print("Sensor value: ");
    lcd.setCursor(0, 1);
    lcd.print(sensor.getValue());

    delay(2000);

    lcd.clear();

    lcd.print("DANGER!");
    lcd.setCursor(0, 1);
    lcd.print("High pollution!");

  } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
    lcd.setRGB(255, 63, 0);

    lcd.setCursor(0, 0);
    lcd.print("Sensor value: ");
    lcd.setCursor(0, 1);
    lcd.print(sensor.getValue());

    delay(2000);

    lcd.clear();

    lcd.print("High pollution!");
  } else if (quality == AirQualitySensor::LOW_POLLUTION) {
    lcd.setRGB(255, 127, 0);

    lcd.setCursor(0, 0);
    lcd.print("Sensor value: ");
    lcd.setCursor(0, 1);
    lcd.print(sensor.getValue());

    delay(2000);

    lcd.clear();

    lcd.print("Low pollution!");
  } else if (quality == AirQualitySensor::FRESH_AIR) {
    lcd.setRGB(0, 255, 0);
    
    lcd.setCursor(0, 0);
    lcd.print("Sensor value: ");
    lcd.setCursor(0, 1);
    lcd.print(sensor.getValue());

    delay(2000);

    lcd.clear();

    lcd.print("Fresh air.");
  }

  delay(5000);

  lcd.clear();
}
