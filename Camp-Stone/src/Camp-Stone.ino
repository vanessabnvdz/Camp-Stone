/*
 * Project Camp_Stone
 * Description: Smart Camp 
 * Author: Vanessa Benavidez
 * Date: August 2 2021
 */

//BME
#include "Adafruit_BME280.h"
Adafruit_BME280 bme;

//OLED
#include "Adafruit_SSD1306.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3c
#define BME_ADDRESS 0x76
float tempC;
float pressPA;
float humidRH;
Adafruit_SSD1306 display(OLED_RESET);

//Air Quality Sensor
#include "Air_Quality_Sensor.h"
AirQualitySensor sensor (A1);
int current_quality;

//Ambient Light Sensor
const int LIGHTSENSOR = A3; 

//Neopixels
#include "neopixel.h"
#include "colors.h"
#define PIXEL_PIN D7
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B
int i; 
const int BRI = 15;
Adafruit_NeoPixel pixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

//FlameSensor
const int FLAMESENSOR = A0;
const int GREENLEDPIN = D5;
const int REDLEDPIN = D4;
int sensorReading; 




void setup() {
  Serial.begin(9600);

//BME
  Serial.begin(9600);
  bme.begin(0x76);
 
 //OLED 
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  delay(5000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();

 //AirQuality
  sensor.init();

//AmbientLightSensor 
  pinMode (LIGHTSENSOR, INPUT);

//Neopixel
  pixel.begin();
  pixel.clear();
  pixel.show();

//FlameSensor
  pinMode (FLAMESENSOR, INPUT);
  pinMode(GREENLEDPIN, OUTPUT); 
  pinMode(REDLEDPIN, OUTPUT);
}

void loop() {

  bmeDisplayed(); 

  readAirquality(); 

  readLight(); 

  readFlame(); 

}


void bmeDisplayed () {
  tempC = bme.readTemperature();
  pressPA = bme.readPressure();
  humidRH = bme.readHumidity();

  display.setCursor(0,0);
  display.clearDisplay();
  display.printf("Temp is %0.1f\n", tempC);
  display.printf("Pressure is %0.1f\n", pressPA);
  display.printf("Humidity is %0.1f\n", humidRH);
  display.display();
}

void readAirquality () {
  current_quality=sensor.slope();
    if (current_quality >= 0)
    {
    if (current_quality==0)
      Serial.println("High pollution! Force signal active");
    else if (current_quality==1)
       Serial.println("High pollution!");
    else if (current_quality==2)
       Serial.println("Low pollution!");
    else if (current_quality==3)
       Serial.println("Fresh air!");
    }
}

void readLight () {
  float reading = analogRead (LIGHTSENSOR); 
  float square_ratio = reading/ 1023.0; 
  square_ratio = pow(square_ratio, 2.0);
  Serial.printf ("Light level is %02f\n", reading); 
  delay (1000); 

    if (reading<150) {
      for (i=0; i<60; i++) {
      pixel.setPixelColor(i, 0xFFFF00);
      pixel.setBrightness(BRI);
      pixel.show();
      }
    } 
    else {
      pixel.clear(); 
      pixel.show();
    }
}

void readFlame () {
  sensorReading = analogRead (FLAMESENSOR); 
  if (FLAMESENSOR == HIGH) {
    digitalWrite (REDLEDPIN, HIGH); 
    digitalWrite (GREENLEDPIN, LOW);
    display.setCursor(0,0);
    display.clearDisplay();
    display.printf("FIRE IS NOT OUT!\n", FLAMESENSOR);
    display.display();
  }
  else {
    digitalWrite (GREENLEDPIN, HIGH); 
    digitalWrite (REDLEDPIN, LOW);
    display.setCursor(0,0);
    display.clearDisplay();
    display.printf("FIRE IS OUT:)\n", FLAMESENSOR);
    display.display();
  }
}