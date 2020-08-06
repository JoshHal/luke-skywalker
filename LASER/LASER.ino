

// defines pins numbers
const int stepXPin = 2;
const int dirXPin = 5;
const int stepYPin = 3;
const int dirYPin = 6;
const int laserPin = 11;



void setup() {
  // Sets the two pins as Outputs
  pinMode(stepXPin, OUTPUT);
  pinMode(dirXPin, OUTPUT);
  pinMode(stepYPin, OUTPUT);
  pinMode(dirYPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);
  for (int x1 ; x1 < 1000 ; x1++) {
    forwarding();
  }
}
void loop() {

  /*
      digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
      // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < 200; x++)
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
      }
      delay(1000); // One second delay

      digitalWrite(dirPin,LOW); //Changes the rotations direction
      // Makes 400 pulses for making two full cycle rotation
      for(int x = 0; x < 400; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
      }
      delay(1000);
  */
}
void forwarding() {
  digitalWrite(dirYPin, HIGH);
  for (int pulse = 0; pulse < 16; pulse++) {
    digitalWrite(stepYPin, HIGH);
    delayMicroseconds(30);
    digitalWrite(stepYPin, LOW);
    delayMicroseconds(30);
  }
  delay(10);
  laser(30);
}
void backward() {
  digitalWrite(dirYPin, LOW);
  for (int pulse2 = 0; pulse2 < 16 ; pulse2++) {
    digitalWrite(stepYPin, HIGH);
    delayMicroseconds(30);
    digitalWrite(stepYPin, LOW);
    delayMicroseconds(30);
  }
  laser(30);
}
void left() {
  digitalWrite(dirXPin, LOW);
  for (int pulse1 = 0; pulse1 < 16 ; pulse1++) {
    digitalWrite(stepXPin, HIGH);
    delayMicroseconds(30);
    digitalWrite(stepXPin, LOW);
    delayMicroseconds(30);
  }
  delay(5);
  laser(30);
}
void Right() {
  digitalWrite(dirXPin, HIGH);
  for (int pulse3 = 0; pulse3 < 16 ; pulse3++) {
    digitalWrite(stepXPin, HIGH);
    delayMicroseconds(30);
    digitalWrite(stepXPin, LOW);
    delayMicroseconds(30);
  }
  delay(10);
  laser(30);
}

void laser(int value) {
  digitalWrite(laserPin, HIGH);
  delay(value);
  digitalWrite(laserPin, LOW);
  delay(1);
}
