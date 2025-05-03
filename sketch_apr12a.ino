#include <ESP32Servo.h>  // ✅ Use ESP32Servo instead of Servo

const int trigPin = 2;
const int echoPin = 4;

const int redLed = 13;
const int yellowLed = 12;
const int greenLed = 14;

const int servoPin = 15;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  myServo.attach(servoPin, 500, 2400); // ✅ ESP32 needs min & max pulse
  myServo.write(0); // Start at 0

  digitalWrite(greenLed, HIGH); // Start with green LED
  Serial.begin(115200);
}

void loop() {
  long duration;
  int distance;

  // Trigger ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println(distance);

  if (distance > 0 && distance <= 15) {
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    delay(5000); // 5 sec
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);

    // Slowly move from 0 to 100
    for (int pos = 0; pos <= 100; pos++) {
      myServo.write(pos);
      delay(15); // smooth animation
    }

    delay(60000); // ✅ 1 minute delay (instead of 3 mins)

    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);

    // Slowly return from 100 to 0
    for (int pos = 100; pos >= 0; pos--) {
      myServo.write(pos);
      delay(15);
    }

    delay(1000); // small yellow delay
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
}
