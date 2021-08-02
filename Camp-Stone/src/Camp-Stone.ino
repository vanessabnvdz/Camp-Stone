/*
 * Project Camp_Stone
 * Description: Smart Camp 
 * Author: Vanessa Benavidez
 * Date: August 2 2021
 */

#include "Adafruit_BME280.h"

Adafruit_BME280 bme;

const int GREENLEDPIN = D5;

const int REDLEDPIN = D4;



void setup() {

pinMode(GREENLEDPIN, OUTPUT); 
pinMode(REDLEDPIN, OUTPUT);
}


void loop() {

digitalWrite(GREENLEDPIN, HIGH);
delay(5000); 
digitalWrite(GREENLEDPIN, LOW); 
digitalWrite(REDLEDPIN, HIGH); 
delay(5000);
digitalWrite(REDLEDPIN, LOW); 
}
