#include<SoftwareSerial.h>
#define txpin 7
#define rxpin 4
#define stepXPin 2
#define dirXPin 5
#define stepYPin 3
#define dirYPin 6
#define laserPin 11
#define TESTBAR 84
#define TESTLINE 71
#define UP 85
#define DOWN 68
#define LEFT 76
#define RIGHT 82
#define SETPOWER 70
#define MARK 102
unsigned char RecivedData1 = 0;
unsigned char RecivedData2 = 0;
unsigned char RecivedData3 = 0;
unsigned char RecivedData4 = 0;
unsigned char Result = 0;
unsigned char Recievedvalue;
int power = 90;
int mm = 0;
int steps = 0;
boolean trigger = 0;
int stepright = 0;
SoftwareSerial Bluetooth = SoftwareSerial(txpin, rxpin);

void setup() {
  pinMode(rxpin, OUTPUT);
  pinMode(txpin, INPUT);
  // Sets the two pins as Outputs
  pinMode(stepXPin, OUTPUT);
  pinMode(dirXPin, OUTPUT);
  pinMode(stepYPin, OUTPUT);
  pinMode(dirYPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);


  Bluetooth.begin(38400);
  Serial.begin(9600);
}

void loop() {
  if (trigger == true) {
    Focus();
  }
  if (Bluetooth.available() > 0) {
    Recievedvalue = Bluetooth.read();
    if (Recievedvalue >= 128) {
      Recievedvalue = Recievedvalue - 128;
      Serial.print(Recievedvalue, DEC);
      Serial.print(' ');     
      plotimage(); 
    } else {
      control();
    }
  }
}
void plotimage(){
  plot(Recievedvalue);
  Right(1);
  stepright+=1;
}
void control() {
  if (Recievedvalue == 120){
    Down(1);
    Serial.print('\n');
    Left(stepright);
    stepright=0;
    Serial.print("returned"); 
  }
  if (Recievedvalue == TESTLINE) testline();
  if (Recievedvalue == TESTBAR) testbar();
  if (Recievedvalue < 50)steps = Recievedvalue;
  if (Recievedvalue == SETPOWER)power = steps * 10;
  if (Recievedvalue == UP) Up(steps * 5);
  if (Recievedvalue == DOWN) Down(steps * 5);
  if (Recievedvalue == LEFT) Left(steps * 5);
  if (Recievedvalue == RIGHT) Right(steps * 5);
  if (Recievedvalue == MARK)trigger = true;
  if (Recievedvalue == 105)trigger = false;
}
void Down(int steps) {
  digitalWrite(dirYPin, HIGH);
  for (int pulse = 0; pulse < steps * 16; pulse++) {
    digitalWrite(stepYPin, HIGH);
    delayMicroseconds(300);
    digitalWrite(stepYPin, LOW);
    delayMicroseconds(250);
  }
  delay(10);
}
void Up(int steps) {
  digitalWrite(dirYPin, LOW);
  for (int pulse2 = 0; pulse2 < steps * 16 ; pulse2++) {
    digitalWrite(stepYPin, HIGH);
    delayMicroseconds( 250);
    digitalWrite(stepYPin, LOW);
    delayMicroseconds( 250);
  }
}
void Right(int steps) {
  digitalWrite(dirXPin, LOW);
  for (int pulse1 = 0; pulse1 < steps * 16 ; pulse1++) {
    digitalWrite(stepXPin, HIGH);
    delayMicroseconds( 250);
    digitalWrite(stepXPin, LOW);
    delayMicroseconds( 250);
  }
}
void Left(int steps) {
  digitalWrite(dirXPin, HIGH);
  for (int pulse3 = 0; pulse3 < steps * 16 ; pulse3++) {
    digitalWrite(stepXPin, HIGH);
    delayMicroseconds( 250);
    digitalWrite(stepXPin, LOW);
    delayMicroseconds( 250);
  }
}
void plot(int value) {     //value= the color number
  for (int burn = 0; burn < power; burn++)
  {
    digitalWrite(laserPin, HIGH);
    delayMicroseconds(value);
  }
  digitalWrite(laserPin, LOW);
}
void Focus() {
  digitalWrite(laserPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(laserPin, LOW);
  delayMicroseconds(300);
}
void testline() {
  for (int pulse = 0; pulse < 250; pulse++) {
    plot(127);
    Right(1);
  }
  Left(250);
}
void testbar() {
  for (int line = 1; line < 20; line++) {
    plot(127);
    Right(1);
    plot(127);
    Right(1);
    for (int pulse = 0; pulse < 127; pulse++) {
      plot(pulse);
      Right(1);
      plot(pulse);
      Right(1);
    }
    Left(127 * 2 + 2);
    Down(1);
  }
}
void pause() {
  digitalWrite(laserPin, LOW);
}
