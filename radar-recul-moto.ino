#include <Grove_LED_Bar.h>

const int CLOCK_PIN = 4; 
const int DATA_PIN = 5;
Grove_LED_Bar bar(CLOCK_PIN, DATA_PIN, 0, LED_BAR_10); // Clock pin, Data pin, Orientation

const int BLUE = 9;
const int GREEN = 10;
const int YELLOW = 11;
const int RED = 12;

const int TRIGGER = 6;
const int ECHO = 7; 

const int REFRESH = 200;

const int GREEN_DIST = 70;
const int YELLOW_DIST = 30;
const int RED_DIST = 15;

const float SOUND_SPEED = 340.0;

int delayChange = 1000;

// the setup function runs once when you press reset or power the board
void setup() {
  bar.begin();
  for(byte i = 1 ; i <= 10 ; i++){
    bar.setLed(i,0);
  }
  
  for(byte i = 10 ; i >= 1 ; i--){
    bar.setLed(i,1);
    delay(50);
  }
  
  for(byte i = 0 ; i <= 10 ; i++){
    bar.setLed(i,0);
    delay(50);
  }
  
  
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
 
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);
  
  digitalWrite(BLUE, HIGH);
  delay(300);  
  digitalWrite(GREEN, HIGH);
  delay(300); 
  digitalWrite(YELLOW, HIGH);
  delay(300); 
  digitalWrite(RED, HIGH);
  delay(300); 

  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);

}

void displayLevelBar(int level){
  for(byte i = 0 ; i < 10 ; i++){
     if( i <= level-1){
        bar.setLed(10-i,1);
     }else{
        bar.setLed(10-i,0);
     }
  }
}

int getLevelFromDist(float distance){

  float longeurTotalMax = GREEN_DIST - RED_DIST;
  int level = 10 - ( 10 * (distance - RED_DIST) ) / (GREEN_DIST - RED_DIST);

  level = level < 0  ? 0 : level;
  level = level > 10 ? 10 : level;
  return level;
}

// the loop function runs over and over again forever
void loop() {
  float distance = readUltrasonicDistance();
  
  /*Serial.print("distance : ");
  Serial.println(distance);
  Serial.print("level : ");
  Serial.println(getLevelFromDist(distance));*/

  displayLevelBar(getLevelFromDist(distance));
  if(distance > 0){
    if(distance > GREEN_DIST) {
       
       digitalWrite(BLUE, HIGH);
       digitalWrite(RED, LOW);
       digitalWrite(YELLOW, LOW);
       digitalWrite(GREEN, LOW);
    } else if(distance <= GREEN_DIST &&  distance > YELLOW_DIST){
      
       digitalWrite(BLUE, LOW);
       digitalWrite(RED, LOW);
       digitalWrite(YELLOW, LOW);
       digitalWrite(GREEN, HIGH);
    } else if(distance <= YELLOW_DIST &&  distance > RED_DIST ){
       
       digitalWrite(BLUE, LOW);
       digitalWrite(RED, LOW);
       digitalWrite(YELLOW, HIGH);
       digitalWrite(GREEN, HIGH);
    } else if(distance <= RED_DIST){
       
       digitalWrite(BLUE, LOW);
       digitalWrite(RED, HIGH);
       digitalWrite(YELLOW, HIGH);
       digitalWrite(GREEN, HIGH);
    }
    delay(REFRESH);
  } 
}





float readUltrasonicDistance() {  
   // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(TRIGGER, LOW);
  digitalWrite(ECHO, LOW);
  delay(10);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  float pulse = pulseIn(ECHO, HIGH); 
  return ((pulse  / 10000) / 2) * SOUND_SPEED; 
}
