// Library for grove led bar
#include <TM1637Display.h>

// Definition for grove led bar

const int CLOCK_PIN = 5; 
const int DATA_PIN = 6;
TM1637Display display(CLOCK_PIN, DATA_PIN);

// Variable for shift register 
#define PIN_DS 8   //pin 14  75HC595    
#define PIN_STCP 9  //pin 12  75HC595
#define PIN_SHCP 10 //pin 11  75HC595
#define PIN_LED_9 11 //pin for 9th led for led barre
#define PIN_LED_10 12 //pin for 10th led for led barre
//How many shift register
#define NUMBER_OF_74hc595 2
// number of total register pin
#define NUM_OF_REGISTER_PINS NUMBER_OF_74hc595 * 8

// Delay de refresh
#define DELAY_SHORT 50 
#define DELAY_LONG DELAY_SHORT * 5

// Create an array with boolean, size of pin of 74hc595
boolean registers[NUM_OF_REGISTER_PINS];

int BAR_LED_PINS[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }; 



// Détector HC SR04
const int TRIGGER = 3;
const int ECHO = 4; 

//Some reference distance to alert
const int GREEN_DIST = 200;
const int RED_DIST = 25;

// Average air sound speed 340 m/s 
const float SOUND_SPEED = 340.0;

/** 
  * the setup function runs once when you press reset or power the board 
  */
void setup() {
  // initialize digital pin for ultrasonic detector
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER,LOW);
  
  // initialize digital pin for shift register
  pinMode(PIN_DS, OUTPUT); 
  pinMode(PIN_STCP, OUTPUT);
  pinMode(PIN_SHCP, OUTPUT);
  digitalWrite(PIN_DS,LOW);
  digitalWrite(PIN_STCP,LOW);
  digitalWrite(PIN_SHCP,LOW);

  // Led 9 & 10 on simple bar led
  pinMode(PIN_LED_9, OUTPUT);
  pinMode(PIN_LED_10, OUTPUT);
  digitalWrite(PIN_LED_9,LOW);
  digitalWrite(PIN_LED_10,LOW);

  //Initialize registers and leds
  switchOffRegisters();
  switchOffLeds();

  display.setBrightness(7);
  display.clear();
  Serial.begin(9600);

  for(int i = 0 ; i <= 1000 ; i = i + 10) {
    display.showNumberDecEx(i);
    delay(10);
  }
  
  // Welcome animation
  animateBarLed();  
}

/** 
  * the loop function runs over and over again forever 
  */
void loop() {
  float distance = readUltrasonicDistance(); 
  distance = distance >= 450 ? 450 : distance;
  int intDistance = (int) distance;
  int level = getLevelFromDist(distance);
  displayLevelBar(level);
  delay(25);  
  display.showNumberDecEx(intDistance,true);
  delay(10);
} 

/**
  * Measure distance in cm
  */

float readUltrasonicDistance() {  
   // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(TRIGGER, LOW);
  digitalWrite(ECHO, LOW);
  delay(10);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIGGER, LOW);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  float pulse = pulseIn(ECHO, HIGH); 
  return ((pulse  / 10000) / 2) * SOUND_SPEED; 
}

/**
  * Get level between 0 & 10 from the distance measured
  */

int getLevelFromDist(float distance){
  int level = 10 - ( 10 * (distance - RED_DIST) ) / (GREEN_DIST - RED_DIST);
  return level <= 0  ? 1 : (level >= 10 ? 10 : level);
}

/**
  * Display level grove bar
  */

void displayLevelBar(int level){
  for(byte i = 0 ; i < 10 ; i++){
      if(i <= level - 1){
        switchOnLed(i);
      }else {
        switchOffLed(i);
      }
      
  }
}

/** 
  * set value recorded in array "registers" and display on the end 
  */
void writeRegisters(){
 // Until LOW modification will not be apply
  digitalWrite(PIN_STCP, LOW);
 // loop for aplly all value for each pin 74hc595
  for(int i = NUM_OF_REGISTER_PINS - 1; i >=  0; i--){
    //need to be low for change column soon
    digitalWrite(PIN_SHCP, LOW);
    // catch value insinde array registers
    int val = registers[i];
    //apply the value to a pin of 74hc595
    digitalWrite(PIN_DS, val);
    // next column
    digitalWrite(PIN_SHCP, HIGH);

  }
  // apply value to all pin of 74hc595
  digitalWrite(PIN_STCP, HIGH); 
  digitalWrite(PIN_LED_9,registers[8] == true ? HIGH : LOW);   
  digitalWrite(PIN_LED_10,registers[9] == true ? HIGH : LOW); 
}

/**
  * Switch on a register 
  */

void switchOnRegister(int pin){
   registers[pin] = HIGH;
   writeRegisters(); 
}
/**
  * Switch off a register 
  */

void switchOffRegister(int pin){
   registers[pin] = LOW;
   writeRegisters(); 
}

/**
  * Switch off all registers 
  */

void switchOffRegisters(){
  clearRegisters();
  writeRegisters();
}

/**
  * Clear all registers
  */

void clearRegisters(){
  for(int i = NUM_OF_REGISTER_PINS - 1; i >=  0; i--){
    registers[i] = LOW;
  }
}

/**
  * Switch on a led 
  */

void switchOnLed(int led) {
  switchOnRegister(BAR_LED_PINS[led]);
  
  
}

/**
  * Switch off a led 
  */

void switchOffLed(int led) {
  switchOffRegister(BAR_LED_PINS[led]); 
  
}

/**
  * Switch off Leds
  */

void switchOffLeds() {
   switchOffRegisters();
   
}

/**
  * Animate simple level by increasing and decreasing one by one level 
  */

void animateSimpleLevel() {
  
  switchOffLeds();
  
  for(int i = 0 ; i < 10 ; i++){
    switchOnLed(i);
    delay(DELAY_SHORT); 
  }

  delay(DELAY_LONG); 
  
  for(int i = 10 ; i > 0 ; i--){
    switchOffLed(i);
    delay(DELAY_SHORT); 
  }

  switchOffLeds();
}

/**
  * Animate from side to center and center to side (left and right)
  */

void animateFromCenterToSideAndReverse() {
  int valueOn1;
  int valueOn2;

  
  for(int i = 0 ; i < 5 ; i++){
    valueOn1 = i;
    valueOn2 = 9 - i;

    for(int j = 10 ; j >= 0 ; j--) { 
      switchOffLed(j);
      if(j == valueOn1 || j == valueOn2) {
        switchOnLed(j);
      }
    }
    delay(DELAY_SHORT); 
  }
  delay(DELAY_LONG); 
  
  for(int i = 5 ; i >= 0 ; i--) {
    valueOn1 = i;
    valueOn2 = 9 - i;

    for(int j = 10 ; j >= 0 ; j--) { 
      switchOffLed(j);
      if(j == valueOn1 || j == valueOn2) {
        switchOnLed(j);
      }
    }
    delay(DELAY_SHORT);
      
  }
  
  delay(DELAY_LONG); 
  
  switchOffLeds();  
  for(int i = 0 ; i < 5 ; i++){
    switchOnLed(i);
    switchOnLed(9 - i);
    delay(DELAY_SHORT);  
  }
  delay(DELAY_LONG);   
  for(int i = 5 ; i >= 0 ; i--){
    switchOffLed(i);
    switchOffLed(9 - i);
    delay(DELAY_SHORT);  
  }
}

/**
  * Animate Bare led
  */
void animateBarLed() {
  animateSimpleLevel();
  delay(DELAY_LONG);
  animateFromCenterToSideAndReverse();
  delay(DELAY_LONG);
}
