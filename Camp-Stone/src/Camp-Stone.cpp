/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/russell/Documents/iot/Camp-Stone/Camp-Stone/src/Camp-Stone.ino"
/*
 * Project Camp_Stone
 * Description: Smart Camp 
 * Author: Vanessa Benavidez
 * Date: August 2 2021
 */


void setup();
void loop();
#line 9 "c:/Users/russell/Documents/iot/Camp-Stone/Camp-Stone/src/Camp-Stone.ino"
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
