/*
This app can use page with DHT & Joy
* - create 4 pages
* - use joystick
* - use LCD: LiquidCrystal 16x2
* - DHT 11 
* - wires
*/

#include <LiquidCrystal.h>
#include <dht.h>

const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
dht DHT;

#define DHT11_PIN A4 // Sensor DHT11 pin A4 
#define joyX A0
#define joyY A1
#define ButtonJoy 8
#define ledY 9

// Number of page |   Count page ==> from 0 ot 5
int numpage = 0, countpage = 5;
long t=0, duration = 0;
int count = 50;
void setup() {
  lcd.begin(16, 2);

  pinMode(ButtonJoy, INPUT_PULLUP);
  pinMode(ledY, OUTPUT);

  t=millis();
}

void loop() {
  duration=millis()-t;

  PossJoy();
  Pages();

  if(duration >= 1000){
     int value = DHT.read11(DHT11_PIN); // Get value from DHT11
     t=millis();
  }
}

void PossJoy(){

  if(digitalRead(ButtonJoy) == LOW){
  delay(100);
  digitalWrite(ledY, HIGH);
  
  }

  else{
    digitalWrite(ledY, LOW);
  }

  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);

  if (xValue >= 0 && yValue <= 10){  // Down 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("down ");
  }
  else{
    
  }

  if (xValue <= 10 && yValue >= 500){ // Left
    delay(200);
    lcd.clear();
    numpage--;
    if (numpage < 0) numpage = 5;
    delay(100);
  }
  else{
    
  }

  if (xValue >= 1015 && yValue >= 500){ // Right
    delay(200);
    lcd.clear();
    numpage++;
    if(numpage > countpage) numpage = 0;
    delay(100);
    
  }
  else{
    
  }

  if (xValue >= 500 && yValue >= 1015){ // Up
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("up ");
  }
  else{
    
  }
}

void Pages(){

  switch (numpage){

    case 0:
    HomePage();
    break;

    case 1:
    Page1();
    break;

    case 2:
    Page2();
    break;

    case 3:
    Page3();
    break;

    case 4:
    Page4();
    break;

    case 5:
    Page5();
    break;
  }
}

void HomePage(){
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("Main App~ DHT");
}

void Page1(){
  ShowNotData();
  ShowCounters();
}

void Page2(){
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");

  ShowCounters();
}

void Page3(){
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.setCursor(0, 1);
  lcd.print(DHT.humidity);
  lcd.print("%");

  ShowCounters();
}

void Page4(){
  ShowNotData();
  ShowCounters();
}

void Page5(){
  ShowNotData();
  ShowCounters();
}

void ShowCounters(){

  lcd.setCursor(15, 1);
  lcd.print(countpage);
  lcd.setCursor(14, 1);
  lcd.print("/");
  lcd.setCursor(13, 1);
  lcd.print(numpage);
}

void ShowNotData(){
    lcd.setCursor(0, 0);
    lcd.print("No Data!");
}