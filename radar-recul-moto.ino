// Library for grove led bar
#include <Grove_LED_Bar.h>

//Définition for grove led bar
const int CLOCK_PIN = 4; 
const int DATA_PIN = 5;
Grove_LED_Bar bar(CLOCK_PIN, DATA_PIN, 0, LED_BAR_10); // Clock pin, Data pin, Orientation

// Détector HC SR04
const int TRIGGER = 6;
const int ECHO = 7; 

//Some reference distance to alert
const int GREEN_DIST = 70;
const int YELLOW_DIST = 30;
const int RED_DIST = 15;

// Average air sound speed 340 m/s 
const float SOUND_SPEED = 340.0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  
  // initialize bar led
  bar.begin();
  
  animateBarLed();
   
}

// the loop function runs over and over again forever
void loop() {
  displayLevelBar(getLevelFromDist(readUltrasonicDistance()));
} 

//Animate to test grove bar led
void animateBarLed(){
  // swith on each led one by one
  for(byte i = 10 ; i >= 1 ; i--){
    bar.setLed(i,1);
    delay(50);
    bar.setLed(i,0);
  }
  // swith off each led one by one
  for(byte i = 0 ; i <= 10 ; i++){
    bar.setLed(i,1);
    delay(50);
    bar.setLed(i,0);
  }

  for(byte i = 10 ; i >= 1 ; i--){
    bar.setLed(i,1);
    delay(50);
   
  }

  // swith off each led one by one
  for(byte i = 0 ; i <= 10 ; i++){
    bar.setLed(i,0);
    delay(50);
  }
}

/**
 * Measure distance in cm
 */

float readUltrasonicDistance() {  
   // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(TRIGGER, LOW);
  digitalWrite(ECHO, LOW);
  delay(1);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  float pulse = pulseIn(ECHO, HIGH); 
  return ((pulse  / 10000) / 2) * SOUND_SPEED; 
}

/**
 * Display level grove bar
 */

void displayLevelBar(int level){
  for(byte i = 0 ; i < 10 ; i++){
      bar.setLed(10-i,(i <= level-1) ? 1 : 0); 
  }
}

/**
 * Get level between 0 & 10 from the distance measured
 */

int getLevelFromDist(float distance){
  float longeurTotalMax = GREEN_DIST - RED_DIST;
  int level = 10 - ( 10 * (distance - RED_DIST) ) / (GREEN_DIST - RED_DIST);
  return level < 0  ? (level > 10 ? 10 : level) : level;
}
