#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define echoPin 3 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 2 //attach pin D3 Arduino to pin Trig of HC-SR04
#define buzzPin 5


long duration; 
int distance;
int height = 25;
int marginH = 90;
int marginL = 10;
int motor = 4;
int status=0;

void setup()
{ pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(motor,   OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Initiating...");
  delay(1000);
}

int distance_cal() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
  return distance;
}

void buzz(){
  digitalWrite(buzzPin,HIGH);
  delay(500);
  digitalWrite(buzzPin,LOW);
  delay(500);
  }
  
void loop(){ 
  Serial.println(status);
  int waterL = height - distance_cal();
  int precentage = waterL * 100 / height ;

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Water Level");
  lcd.setCursor(5, 1);
  lcd.print(String(precentage) + " %");
  delay(100);
  if (precentage <= marginL) {
    digitalWrite(motor,LOW);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Water Level");
    lcd.setCursor(5, 1);
    lcd.print("Low");
    delay(100);
    buzz();
    status=0;
    
  }
  if (precentage >= marginH ) {
    digitalWrite(motor,HIGH);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Water Level");
    lcd.setCursor(5, 1);
    lcd.print("High");
    delay(100);
    if(status==0){
      for(int i=0;i<5;i++){
    buzz();}
    status=1;}

}
}
